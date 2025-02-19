//==============================================================================
//
//  This file is part of GNSSTk, the ARL:UT GNSS Toolkit.
//
//  The GNSSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GNSSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GNSSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//
//  This software was developed by Applied Research Laboratories at the
//  University of Texas at Austin.
//  Copyright 2004-2022, The Board of Regents of The University of Texas System
//
//==============================================================================

//==============================================================================
//
//  This software was developed by Applied Research Laboratories at the
//  University of Texas at Austin, under contract to an agency or agencies
//  within the U.S. Department of Defense. The U.S. Government retains all
//  rights to use, duplicate, distribute, disclose, or release this software.
//
//  Pursuant to DoD Directive 523024
//
//  DISTRIBUTION STATEMENT A: This software has been approved for public
//                            release, distribution is unlimited.
//
//==============================================================================

// This program is intended to help differencing data files and not
// failing on small differences in floating point values.


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <set>

#include "BasicFramework.hpp"
#include "StringUtils.hpp"

using namespace std;

class DFDiff : public gnsstk::BasicFramework
{
public:
   DFDiff(const string& applName)
      noexcept
      : gnsstk::BasicFramework(
         applName,
         "Differences two input files while allowing small differences"
         " in floating point values."),
        epsilon(1e-5),
        linesToSkip(0),
        lastlineValue(0),
        totalLines(0)
   {};


      /// Structure that defines column and regular expression to ignore.
   struct RegExcludeCol
   {
      unsigned col;
      string regex;
   };

      // While this is in C11, we don't want to work under C03
   double stringToDouble(const string& s, bool& isDouble)
   {
      char *p;
      double v = strtod(s.c_str(), &p);
      if (p == s.c_str())
         isDouble = false;
      else
         isDouble = true;
      return v;
   }

   bool initialize(int argc, char *argv[]) noexcept
   {
      gnsstk::CommandOptionWithAnyArg
         input1Option('1', "input1", "First file to take the input from.", true),
         input2Option('2', "input2", "Second file to take the input from.", true),
         lineSkipOption('l', "lines", "Number of lines to skip at beginning of file."),
         epsilonOption('e', "epsilon", "Percent allowable difference in floating point values."),
         outputOption('o', "output", "A file to receive the output. The default is stdout."),
         regexOption('X', "regexclude", "Exclude lines matching a regular"
                     " expression"),
         igregOption('I', "ign-reg", "Ignore column X (starting with 0) on"
                     " lines matching regular expression Y, ARG=X,Y"),
         lastLineOption('z', "last", "ignore the last X lines of the file");

      if (!BasicFramework::initialize(argc,argv))
         return false;

      input1Fn = input1Option.getValue()[0];
      input2Fn = input2Option.getValue()[0];

      input1.open(input1Fn.c_str(), istringstream::in);
      input2.open(input2Fn.c_str(), istringstream::in);

      if (!input1)
      {
         cerr << "Could not open: " << input1Fn << endl;
         exitCode=1;
         return false;
      }

      if (!input1)
      {
         cerr << "Could not open: " << input2Fn << endl;
         exitCode=1;
         return false;
      }

         // Determine total number of lines in input file 1
      string line;
      while (getline(input1, line))
         totalLines++;

      if (debugLevel)
         cout << "File 1 has " << totalLines << " lines" << endl;

         // Determine how many lines to ignore at the end of the file
      if (lastLineOption.getCount())
         lastlineValue = gnsstk::StringUtils::asInt(lastLineOption.getValue()[0]);

      totalLines = totalLines - lastlineValue;

         // clear and reset the buffer for input file 1
      input1.clear();
      input1.seekg(0,ios::beg);

      if (outputOption.getCount())
         outputFn = outputOption.getValue()[0];

      if (outputFn=="-" || outputFn=="")
      {
         output.copyfmt(cout);
         output.clear(cout.rdstate());
         output.ios::rdbuf(cout.rdbuf());
         outputFn = "<stdout>";
      }
      else
      {
         output.open(outputFn.c_str(), ios::out);
      }

      if (!output)
      {
         cerr << "Could not open: " << outputFn << endl;
         exitCode=1;
         return false;
      }

      if (epsilonOption.getCount())
         epsilon = gnsstk::StringUtils::asDouble(epsilonOption.getValue()[0]);

      if (lineSkipOption.getCount())
         linesToSkip = gnsstk::StringUtils::asInt(lineSkipOption.getValue()[0]);

      if (regexOption.getCount())
         regexclude = regexOption.getValue();

      if (igregOption.getCount())
      {
         vector<string> igvec(igregOption.getValue());
         for (unsigned i = 0; i < igvec.size(); i++)
         {
            if (gnsstk::StringUtils::numWords(igvec[i],',') < 2)
            {
               cerr << "Invalid spec \"" << igvec[i]
                    << "\", expecting column,regex" << endl;
               exitCode = gnsstk::BasicFramework::OPTION_ERROR;
               return false;
            }
            string colStr = gnsstk::StringUtils::firstWord(igvec[i],',');
            if (!gnsstk::StringUtils::isDigitString(colStr))
            {
               cerr << "Invalid spec \"" << igvec[i]
                    << "\", expecting column,regex" << endl;
               exitCode = gnsstk::BasicFramework::OPTION_ERROR;
               return false;
            }
            RegExcludeCol rec;
            rec.col = gnsstk::StringUtils::asUnsigned(colStr);
            rec.regex = gnsstk::StringUtils::words(igvec[i],1,string::npos,',');
            recs.push_back(rec);
         }
      }

      if (debugLevel)
         output << "First file " << input1Fn << endl
                << "Second file " << input2Fn << endl
                << "Output file " << outputFn << endl
                << "Epsilon " << epsilon << endl
                << "Skipping " << linesToSkip << " lines at beginning" << endl
                << "Skipping " << lastlineValue << " lines at end" << endl;

      return true;
   }

protected:
   virtual void spinUp()
   {}

   virtual void process()
   {
      try
      {
         for (long lineNumber = 1; lineNumber < totalLines; lineNumber++)
         {
            string line1, line2;
            if (!getline(input1, line1) || !getline(input2, line2))
            {
               exitCode++;
               break;
            }

            if (lineNumber <= linesToSkip)
               continue;

               // Try to match BOTH lines with each user-specified
               // regular expression.  If they both match, skip the
               // line.  If only one matches, that counts as a
               // difference.
            bool skipregex = false;
            for (unsigned i = 0; i < regexclude.size(); i++)
            {
               if (gnsstk::StringUtils::isLike(line1, regexclude[i]) &&
                   gnsstk::StringUtils::isLike(line2, regexclude[i]))
               {
                  skipregex = true;
                  break;
               }
            }
            if (skipregex)
               continue;

            string s1, s2;
            istringstream ss1(line1);
            istringstream ss2(line2);
            bool lineDiff = false;
            unsigned column = 0;
            set<unsigned> skipCols;
               // collect the columns to ignore due to matching regular expr.
            for (unsigned i = 0; i < recs.size(); i++)
            {
               if (gnsstk::StringUtils::isLike(line1, recs[i].regex) &&
                   gnsstk::StringUtils::isLike(line2, recs[i].regex))
               {
                  skipCols.insert(recs[i].col);
               }
            }
            while ((ss1 >> s1) && (ss2 >> s2))
            {
               if (skipCols.count(column++))
               {
                  continue;
               }
               if (s1 != s2)
               {
                  bool df1,df2;
                  double d1 = stringToDouble(s1, df1);
                  double d2 = stringToDouble(s2, df2);
                  if (df1 && df2)
                  {
                     double diff = d1-d2;
                     double err = d2;
                     if (d1 != 0)
                        err = diff/d1;

                     if (abs(err) > epsilon)
                     {
                        exitCode += 1;
                        lineDiff = true;
                     }
                  }
                  else
                  {
                     exitCode += 1;
                     lineDiff = true;
                  }

                  if (verboseLevel && lineDiff)
                  {
                     output << "f1, " << lineNumber << ":" << line1 << endl
                            << "f2, " << lineNumber << ":" << line2 << endl;
                  }
               }
            }
         }
      }
      catch (std::exception& e)
      {
         cout << e.what() << endl;
         exitCode += 1;
      }

      if (verboseLevel)
         output << "Total differences: " << exitCode << endl;

   }

   virtual void shutDown()
   {}

   string input1Fn, input2Fn, outputFn;
   ofstream output;
   ifstream input1, input2;
   double epsilon;
   vector<string> regexclude;
   vector<RegExcludeCol> recs;
public:
   long linesToSkip;
   long totalLines;
   int lastlineValue;
};


int main(int argc, char *argv[])
{
   DFDiff crap(argv[0]);

   if (crap.initialize(argc, argv))
      crap.run();

   return crap.exitCode;
}


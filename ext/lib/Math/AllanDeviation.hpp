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

/**
 * @file AllanDeviation.hpp
 * Computes the overlapping Allan variance of a pair of vectors.
 */

#ifndef GNSSTK_ALLANDEVIATION_HPP
#define GNSSTK_ALLANDEVIATION_HPP

#include <vector>
#include <cmath>
#include <ostream>

#include "Exception.hpp"

namespace gnsstk
{
   /// @ingroup MathGroup
   //@{


   /// Compute the overlapping Allan variance of the phase data provided.
   class AllanDeviation
   {
   public:
         /**
          * @throw Exception
          */
      AllanDeviation(std::vector<double>& phase, double tau0)
         : N(phase.size()-1), numGaps(0)
      {
         if(N < 1 )
         {
            Exception e("Need more than 2 point to compute a meaningful allan variance.");
            GNSSTK_THROW(e);
         }

         // Actual Overlapping Allan Deviation Calculation is done here
         // The Overlapping Allan Deviation is calculated as follows
         //  Sigma^2(Tau) = 1 / (2*(N-2*m)*Tau^2) * Sum(X[i+2*m]-2*X[i+m]+X[i], i=1, i=N-2*m)
         //  Where Tau is the averaging time, N is the total number of points, and Tau = m*Tau0
         //  Where Tau0 is the basic measurement interval
         double sum, sigma;
         for(int m = 1; m <= (N-1)/2; m++)
         {
            double tau = m*tau0;
            sigma = 0;

            for(int i = 0; i < (N-2*m); i++)
            {
               sum = 0;
               if((phase[i+2*m]==0 ||  phase[i+m]==0 || phase[i]==0)
                  && i!=0 && i!=(N-2*m-1))
                  numGaps++;
               else
                  sum = phase[i+2*m] - 2*phase[i+m] + phase[i];
               sigma += sum * sum;
            }

            sigma = sigma / (2.0*((double)N-(double)numGaps-0-2.0*(double)m)*tau*tau);
            sigma = ::sqrt(sigma);
            deviation.push_back(sigma);
            time.push_back(tau);
         }
      }

      void dump(std::ostream& s = std::cout) const noexcept
      {
         std::vector<double>::const_iterator i=deviation.begin(),j=time.begin();
         for (; i != deviation.end() && j != time.end(); i++,j++)
            s << *j << "  " << *i << std::endl;
      };

      const int N;
      std::vector<double> deviation, time;
      int numGaps;
   };

   std::ostream& operator<<(std::ostream& s, const AllanDeviation& a)
   {
      a.dump(s);
      return s;
   }

}  // namespace

#endif

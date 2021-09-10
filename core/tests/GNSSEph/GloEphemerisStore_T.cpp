//==============================================================================
//
//  This file is part of GNSSTk, the GNSS Toolkit.
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
//  Copyright 2004-2021, The Board of Regents of The University of Texas System
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

#include "Exception.hpp"
#include "GloEphemerisStore.hpp"
#include "CivilTime.hpp"
#include "TimeString.hpp"
#include "TestUtil.hpp"
#include "GPSWeekSecond.hpp"
#include "Rinex3NavStream.hpp"
#include "Rinex3NavData.hpp"
#include "SatelliteSystem.hpp"

using namespace std;

namespace gnsstk
{
   ostream& operator<<(ostream& s, const gnsstk::SatelliteSystem sys)
   {
      s << gnsstk::StringUtils::asString(sys);
      return s;
   }
}

class OrbElemStore_T
{
public:
   std::string inputRN3Data;

   OrbElemStore_T()
   {
      std::string dataFilePath = gnsstk::getPathData();
      std::string tempFilePath = gnsstk::getPathTestTemp();
      std::string fileSep = gnsstk::getFileSep();

      inputRN3Data = dataFilePath + fileSep + "mixed.06n";
   }


      /** This tests the behavior of OrbElemStore when the store is
       * empty.  Under normal circumstances the map for a given
       * satellite would not be empty, but that can't be guaranteed as
       * soon as edit() is used. */
   unsigned doFindEphEmptyTests()
   {
      TUDEF("OrbElemStore","Empty Store Tests");
      try
      {
         gnsstk::GloEphemerisStore store;
         gnsstk::Rinex3NavData nd = loadNav(store, testFramework, true);
         TUASSERTE(gnsstk::SatelliteSystem,
                   gnsstk::SatelliteSystem::Glonass, nd.sat.system);
         gnsstk::CommonTime searchTime(nd.time);
         gnsstk::SatID sat(nd.sat);

            // make sure the ephemeris is in the store
         TUCSM("size");
         TUASSERTE(unsigned, 1, store.size());

            // make sure we can find it
         TUCSM("findNearEphemeris");
         TUCATCH(store.findNearEphemeris(sat, searchTime));

         TUCSM("findEphemeris");
         TUCATCH(store.findEphemeris(sat, searchTime));

            // remove the ephemeris
         TUCSM("edit");
         store.edit(store.getFinalTime() + 604800);

            // make sure the ephemeris has been removed
         TUCSM("size");
         TUASSERTE(unsigned, 0, store.size());

            // make sure we can't find it and don't seg fault
         TUCSM("findNearEphemeris");
         try 
         {
            const gnsstk::GloEphemeris& ge =
               store.findNearEphemeris(sat, searchTime); 
            TUFAIL("Called findNearEphemeris for empty store and FAILED to"
                   " throw InvalidRequest");
         }
         catch (gnsstk::InvalidRequest)
         {
            TUPASS("Called findNearEphemeris for empty store and received"
                   " InvalidRequest as expected.");
         }

         TUCSM("findEphemeris");
         try 
         {
            const gnsstk::GloEphemeris& ge =
               store.findEphemeris(sat, searchTime); 
            TUFAIL("Called findEphemeris for empty store and FAILED to"
                   " throw InvalidRequest");
         }
         catch (gnsstk::InvalidRequest)
         {
            TUPASS("Called findEphemeris for empty store and received"
                   " InvalidRequest as expected.");
         }
      }
      catch (gnsstk::Exception &exc)
      {
         cerr << exc << endl;
         TUFAIL("Unexpected exception");
      }
      catch (...)
      {
         TUFAIL("Unexpected exception");
      }
      TURETURN();
   }


   unsigned computeXvtTest()
   {
      TUDEF("GloEphemerisStore", "computeXvt");
      try
      {
         gnsstk::GloEphemerisStore store;
         gnsstk::Rinex3NavData nd = loadNav(store, testFramework, false);
         gnsstk::Xvt rv;
         gnsstk::SatID fake(933, gnsstk::SatelliteSystem::Glonass);
         TUCATCH(rv = store.computeXvt(nd.sat, nd.time));
         TUASSERTE(gnsstk::Xvt::HealthStatus,
                   gnsstk::Xvt::HealthStatus::Healthy, rv.health);
         TUCATCH(rv = store.computeXvt(fake, nd.time));
         TUASSERTE(gnsstk::Xvt::HealthStatus,
                   gnsstk::Xvt::HealthStatus::Unavailable, rv.health);
      }
      catch (...)
      {
         TUFAIL("Unexpected exception");
      }
      TURETURN();
   }


   unsigned getSVHealthTest()
   {
      TUDEF("GloEphemerisStore", "getSVHealth");
      try
      {
         gnsstk::GloEphemerisStore store;
         gnsstk::Rinex3NavData nd = loadNav(store, testFramework, false);
         gnsstk::Xvt::HealthStatus rv;
         gnsstk::SatID fake(933, gnsstk::SatelliteSystem::Glonass);
         TUCATCH(rv = store.getSVHealth(nd.sat, nd.time));
         TUASSERTE(gnsstk::Xvt::HealthStatus,
                   gnsstk::Xvt::HealthStatus::Healthy, rv);
         TUCATCH(rv = store.getSVHealth(fake, nd.time));
         TUASSERTE(gnsstk::Xvt::HealthStatus,
                   gnsstk::Xvt::HealthStatus::Unavailable, rv);
      }
      catch (...)
      {
         TUFAIL("Unexpected exception");
      }
      TURETURN();
   }


   gnsstk::Rinex3NavData loadNav(gnsstk::GloEphemerisStore& store,
                                gnsstk::TestUtil& testFramework,
                                bool firstOnly)
   {
      gnsstk::Rinex3NavStream ns(inputRN3Data.c_str());
      gnsstk::Rinex3NavHeader nh;
      gnsstk::Rinex3NavData nd;
      TUASSERT(ns.good());
      ns >> nh;
      TUASSERT(ns.good());
      ns >> nd;
      if (firstOnly)
      {
         while ((nd.sat.system != gnsstk::SatelliteSystem::Glonass) && ns)
         {
            ns >> nd;
         }
         if (nd.sat.system != gnsstk::SatelliteSystem::Glonass)
         {
               // somehow got through the source file without any GLONASS data
            TUFAIL("input file did not contain GLONASS data");
            return nd;
         }
         TUASSERT(store.addEphemeris(nd));
      }
      else
      {
         while (ns)
         {
            ns >> nd;
            if (nd.sat.system == gnsstk::SatelliteSystem::Glonass)
            {
               TUASSERT(store.addEphemeris(nd));
            }
         }
      }
      return nd;
   }

};


int main(int argc, char *argv[])
{
   unsigned total = 0;
   OrbElemStore_T testClass;
   total += testClass.doFindEphEmptyTests();
   total += testClass.computeXvtTest();
   total += testClass.getSVHealthTest();

   cout << "Total Failures for " << __FILE__ << ": " << total << endl;
   return total;
}

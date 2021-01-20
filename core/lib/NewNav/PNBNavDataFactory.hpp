//==============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 3.0 of the License, or
//  any later version.
//
//  The GPSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GPSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//  
//  This software was developed by Applied Research Laboratories at the 
//  University of Texas at Austin.
//  Copyright 2004-2020, The Board of Regents of The University of Texas System
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
#ifndef GPSTK_PNBNAVDATAFACTORY_HPP
#define GPSTK_PNBNAVDATAFACTORY_HPP

#include <memory>
#include <map>
#include "PackedNavBits.hpp"
#include "NavData.hpp"
#include "NavValidityType.hpp"

namespace gpstk
{
      /// @ingroup NavFactory
      //@{

      /** This is the abstract base class for all PackedNavBits
       * decoders for theNavData tree.  Only one method is declared,
       * addData(), which is the intended interface to be used.  This
       * particular tree of classes implement the code necessary to
       * convert a stream of PackedNavBits objects into the
       * appropriate NavData objects.  This is not a 1:1
       * correlation. */
   class PNBNavDataFactory
   {
   public:
         /** Initialize navValidity to All and procNavTypes to all
          * known message types. */
      PNBNavDataFactory();

         /** Set the factory's handling of valid and invalid
          * navigation data.  This should be called before any addData()
          * calls.
          * @param[in] nvt The new nav data loading filter method. */
      virtual void setValidityFilter(NavValidityType nvt)
      { navValidity = nvt; }

         /** Indicate what nav message types the factories should be
          * loading.  This should be called before any addData()
          * calls.
          * @param[in] nmts The set of nav message types to be
          *   processed by the factories. */
      virtual void setTypeFilter(const NavMessageTypeSet& nmts);

         /** Process a PackedNavBits object, producing NavData objects
          * as appropriate.
          * @param[in] navIn The PackedNavBits data to process.
          * @param[out] navOut Any resulting NavData objects that were
          *   completed, usually as a result of adding navIn to the
          *   set of data.
          * @param[in] cadence The data rate of the navigation
          *   messages being processed.  If cadence < 0, The default
          *   values of NavData::msgLenSec will be used. Values >= 0
          *   will override the default.
          * @return false on error. */
      virtual bool addData(const PackedNavBitsPtr& navIn,
                           NavDataPtrList& navOut,
                           double cadence = -1) = 0;

         /** Reset the state of the data accumulator.  Most
          * PNBNavDataFactory child classes will maintain some state
          * to assemble data prior to processing.  This method is
          * intended to be used to clear out that intermediate data to
          * start from a fresh state, e.g. if you're loading
          * discontinuous data. */
      virtual void resetState() = 0;

   protected:
         /// Determines how the factory should filter added data.
      NavValidityType navValidity;

         /// If true, ephemeris data will be output by addData.
      bool processEph;
         /// If true, almanac data will be output by addData.
      bool processAlm;
         /// If true, health data will be output by addData.
      bool processHea;
         /// If true, time offset data will be output by addData.
      bool processTim;
   }; // class PNBNavDataFactory

      /// Managed pointer to a PNBNavDataFactory.
   using PNBNavDataFactoryPtr = std::shared_ptr<PNBNavDataFactory>;
      /// Map the navigation message type to a factory for producing that type.
   using PNBNavDataFactoryMap = std::map<NavType, PNBNavDataFactoryPtr>;

      //@}

} // namespace gpstk

#endif // GPSTK_PNBNAVDATAFACTORY_HPP

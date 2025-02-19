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
#ifndef GNSSTK_GPSLNAVTIMEOFFSET_HPP
#define GNSSTK_GPSLNAVTIMEOFFSET_HPP

#include "StdNavTimeOffset.hpp"
#include "TimeSystem.hpp"

namespace gnsstk
{
      /// @ingroup NavFactory
      //@{

      /** Defines the class that provides the ability to convert
       * between GPS and UTC, using data extracted from GPS legacy
       * navigation messages. */
   class GPSLNavTimeOffset : public StdNavTimeOffset
   {
   public:
         /// Initialize all data to 0.
      GPSLNavTimeOffset();
         /// Create a deep copy of this object.
      NavDataPtr clone() const override
      { return std::make_shared<GPSLNavTimeOffset>(*this); }

         /** Checks the contents of this message against known
          * validity rules as defined in the appropriate ICD.
          * @return true if this message is valid according to ICD criteria.
          */
      bool validate() const override;
   };

      //@}

}

#endif // GNSSTK_GPSLNAVTIMEOFFSET_HPP

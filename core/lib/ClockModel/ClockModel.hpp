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
 * @file ClockModel.hpp
 * An abstract class to provide an interface to a model of a clock offset.
 * The model neds to be able to return an offset value at an indicated
 * point in time.
 */

#ifndef CLOCKMODEL_HPP
#define CLOCKMODEL_HPP

#include <map>
#include "Exception.hpp"
#include "CommonTime.hpp"

/**
 * This is a abstract base class for a clock model
 */

namespace gnsstk
{
      /// @ingroup ClockModel
      //@{

   class ClockModel
   {
   public:
      ClockModel() noexcept {};

      virtual double getOffset(const gnsstk::CommonTime& t) const = 0;

      virtual bool isOffsetValid(const gnsstk::CommonTime& t) const = 0;

   };

      //@}

}
#endif

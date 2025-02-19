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

#ifndef LNAVCOOKFILTER_HPP
#define LNAVCOOKFILTER_HPP

#include "NavFilter.hpp"
#include "LNavFilterData.hpp"

namespace gnsstk
{
      /// @ingroup NavFilter
      //@{

      /** "Cook" GPS legacy nav messages by turning words upright.
       * Data in LNavFilterData::sf are modified.
       *
       * @attention Processing depth = 1 epoch. */
   class LNavCookFilter : public NavFilter
   {
   public:
      LNavCookFilter();

         /** Turn words in a GPS LNAV message upright.  This results
          * in the expected 0x8b preamble in the TLM and subsequent
          * bits as expected per the IS-GPS-200.
          * @pre LNavFilterData::sf is set
          * @param[in,out] msgBitsIn a list of LNavFilterData* objects
          *   containing GPS LNAV data.
          * @param[out] msgBitsOut the "cooked" subframes.  All
          *   contents of msgBitsIn will be immediately seen in
          *   msgBitsOut. */
      virtual void validate(NavMsgList& msgBitsIn, NavMsgList& msgBitsOut);

         /// Filter stores no data, therefore this does nothing.
      virtual void finalize(NavMsgList& msgBitsOut)
      {}

         /// No internal storage of subframe data so return 0.
      virtual unsigned processingDepth() const noexcept
      { return 0; }

         /// Turn an LNAV subframe data upright.
      static void cookSubframe(LNavFilterData* fd);

         /// Return the filter name.
      virtual std::string filterName() const noexcept
      { return "Cook"; }
   };

      //@}
}

#endif // LNAVCOOKFILTER_HPP

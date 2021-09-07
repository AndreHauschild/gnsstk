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
/** @file GalINavTestDataDef.hpp This file contains data definitions
 * for testing Galileo I/NAV processing in the NavFactory code. */

oidINAVGal = gnsstk::ObsID(gnsstk::ObservationType::NavMsg,
                          gnsstk::CarrierBand::L1,
                          gnsstk::TrackingCode::E1B);
ephINAVGalWT2ct = gnsstk::GALWeekSecond(1014,518401);
ephINAVGalWT4ct = gnsstk::GALWeekSecond(1014,518403);
navINAVGalWT6ct = gnsstk::GALWeekSecond(1014,518405);
navINAVGalWT7ct = gnsstk::GALWeekSecond(1014,518407);
navINAVGalWT8ct = gnsstk::GALWeekSecond(1014,518409);
ephINAVGalWT1ct = gnsstk::GALWeekSecond(1014,518421);
ephINAVGalWT3ct = gnsstk::GALWeekSecond(1014,518423);
ephINAVGalWT5ct = gnsstk::GALWeekSecond(1014,518425);
navINAVGalWT9ct = gnsstk::GALWeekSecond(1014,518437);
navINAVGalWT10ct = gnsstk::GALWeekSecond(1014,518439);
ephINAVGalSid = gnsstk::SatID(1,gnsstk::SatelliteSystem::Galileo);

ephINAVGalWT1 = std::make_shared<gnsstk::PackedNavBits>(ephINAVGalSid,oidINAVGal,
                                                       ephINAVGalWT1ct);
ephINAVGalWT1->setNavID(gnsstk::NavType::GalINAV);
ephINAVGalWT1->addUnsignedLong(0x045E86B2,32,1);
ephINAVGalWT1->addUnsignedLong(0x14606028,32,1);
ephINAVGalWT1->addUnsignedLong(0x0039B8BE,32,1);
ephINAVGalWT1->addUnsignedLong(0xA813EC77,32,1);
ephINAVGalWT1->trimsize();

ephINAVGalWT2 = std::make_shared<gnsstk::PackedNavBits>(ephINAVGalSid,oidINAVGal,
                                                       ephINAVGalWT2ct);
ephINAVGalWT2->setNavID(gnsstk::NavType::GalINAV);
ephINAVGalWT2->addUnsignedLong(0x085E78BB,32,1);
ephINAVGalWT2->addUnsignedLong(0x0E292854,32,1);
ephINAVGalWT2->addUnsignedLong(0x403C05B7,32,1);
ephINAVGalWT2->addUnsignedLong(0x23FFF7FD,32,1);
ephINAVGalWT2->trimsize();

ephINAVGalWT3 = std::make_shared<gnsstk::PackedNavBits>(ephINAVGalSid,oidINAVGal,
                                                       ephINAVGalWT3ct);
ephINAVGalWT3->setNavID(gnsstk::NavType::GalINAV);
ephINAVGalWT3->addUnsignedLong(0x0C5EFFC8,32,1);
ephINAVGalWT3->addUnsignedLong(0x1B1BAB09,32,1);
ephINAVGalWT3->addUnsignedLong(0xAB19670C,32,1);
ephINAVGalWT3->addUnsignedLong(0x0B0C496B,32,1);
ephINAVGalWT3->trimsize();

ephINAVGalWT4 = std::make_shared<gnsstk::PackedNavBits>(ephINAVGalSid,oidINAVGal,
                                                       ephINAVGalWT4ct);
ephINAVGalWT4->setNavID(gnsstk::NavType::GalINAV);
ephINAVGalWT4->addUnsignedLong(0x105E07FF,32,1);
ephINAVGalWT4->addUnsignedLong(0xE3FFFA1A,32,1);
ephINAVGalWT4->addUnsignedLong(0xCFEE8486,32,1);
ephINAVGalWT4->addUnsignedLong(0xFFFDC601,32,1);
ephINAVGalWT4->trimsize();

ephINAVGalWT5 = std::make_shared<gnsstk::PackedNavBits>(ephINAVGalSid,oidINAVGal,
                                                       ephINAVGalWT5ct);
ephINAVGalWT5->setNavID(gnsstk::NavType::GalINAV);
ephINAVGalWT5->addUnsignedLong(0x145B82A0,32,1);
ephINAVGalWT5->addUnsignedLong(0x0581F67D,32,1);
ephINAVGalWT5->addUnsignedLong(0x401FB3F4,32,1);
ephINAVGalWT5->addUnsignedLong(0x8CAAAAAA,32,1);
ephINAVGalWT5->trimsize();

navINAVGalWT6 = std::make_shared<gnsstk::PackedNavBits>(ephINAVGalSid,oidINAVGal,
                                                       navINAVGalWT6ct);
navINAVGalWT6->setNavID(gnsstk::NavType::GalINAV);
navINAVGalWT6->addUnsignedLong(0x1BFFFFFF,32,1);
navINAVGalWT6->addUnsignedLong(0xFC000004,32,1);
navINAVGalWT6->addUnsignedLong(0x49E3DA27,32,1);
navINAVGalWT6->addUnsignedLong(0x893F482A,32,1);
navINAVGalWT6->trimsize();

navINAVGalWT7 = std::make_shared<gnsstk::PackedNavBits>(ephINAVGalSid,oidINAVGal,
                                                       navINAVGalWT7ct);
navINAVGalWT7->setNavID(gnsstk::NavType::GalINAV);
navINAVGalWT7->addUnsignedLong(0x1FAD7930,32,1);
navINAVGalWT7->addUnsignedLong(0x060076C8,32,1);
navINAVGalWT7->addUnsignedLong(0x7F3A46A7,32,1);
navINAVGalWT7->addUnsignedLong(0xFC5DAF15,32,1);
navINAVGalWT7->trimsize();

navINAVGalWT8 = std::make_shared<gnsstk::PackedNavBits>(ephINAVGalSid,oidINAVGal,
                                                       navINAVGalWT8ct);
navINAVGalWT8->setNavID(gnsstk::NavType::GalINAV);
navINAVGalWT8->addUnsignedLong(0x23BFFEC0,32,1);
navINAVGalWT8->addUnsignedLong(0x00002AAA,32,1);
navINAVGalWT8->addUnsignedLong(0xAAAAAAAA,32,1);
navINAVGalWT8->addUnsignedLong(0xAAAAAAAA,32,1);
navINAVGalWT8->trimsize();

navINAVGalWT9 = std::make_shared<gnsstk::PackedNavBits>(ephINAVGalSid,oidINAVGal,
                                                       navINAVGalWT9ct);
navINAVGalWT9->setNavID(gnsstk::NavType::GalINAV);
navINAVGalWT9->addUnsignedLong(0x27AD7955,32,1);
navINAVGalWT9->addUnsignedLong(0x55555555,32,1);
navINAVGalWT9->addUnsignedLong(0x5EA80600,32,1);
navINAVGalWT9->addUnsignedLong(0x390AC83F,32,1);
navINAVGalWT9->trimsize();

navINAVGalWT10 = std::make_shared<gnsstk::PackedNavBits>(ephINAVGalSid,
                                                        oidINAVGal,
                                                        navINAVGalWT10ct);
navINAVGalWT10->setNavID(gnsstk::NavType::GalINAV);
navINAVGalWT10->addUnsignedLong(0x2B9E283F,32,1);
navINAVGalWT10->addUnsignedLong(0x945097F7,32,1);
navINAVGalWT10->addUnsignedLong(0x8FFFC3FC,32,1);
navINAVGalWT10->addUnsignedLong(0x9FFC6436,32,1);
navINAVGalWT10->trimsize();


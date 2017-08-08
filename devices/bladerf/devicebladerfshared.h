///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef DEVICES_BLADERF_DEVICEHACKRFSHARED_H_
#define DEVICES_BLADERF_DEVICEHACKRFSHARED_H_

#include "util/message.h"

class DeviceBladeRFShared
{
public:
    static const float  m_sampleFifoLengthInSeconds;
    static const int    m_sampleFifoMinSize;
    static const int    m_sampleFifoMinSize32;
};


#endif /* DEVICES_BLADERF_DEVICEHACKRFSHARED_H_ */

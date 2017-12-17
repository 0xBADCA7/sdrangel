///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2017 Edouard Griffiths, F4EXB.                                  //
//                                                                               //
// Swagger server adapter interface                                              //
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

#ifndef SDRSRV_MAINCORE_H_
#define SDRSRV_MAINCORE_H_

#include <QObject>
#include "util/export.h"

class AudioDeviceInfo;
class DSPEngine;
class DSPDeviceSourceEngine;
class DSPDeviceSinkEngine;
class DeviceSourceAPI;
class DeviceSinkAPI;
class PluginAPI;
class PluginInterface;
class PluginManager;
class ChannelMarker;
class DeviceSet; // TODO: create this class
class WebAPIRequestMapper;
class WebAPIServer;
class WebAPIAdapterSrv; // TODO: create this class

class SDRANGEL_API MainCore : public QObject {
    Q_OBJECT
};




#endif /* SDRSRV_MAINCORE_H_ */
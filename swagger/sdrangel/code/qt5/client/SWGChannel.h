/**
 * SDRangel
 * This is the web API of SDRangel SDR software. SDRangel is an Open Source Qt5/OpenGL 3.0+ GUI and server Software Defined Radio and signal analyzer in software. It supports Airspy, BladeRF, HackRF, LimeSDR, PlutoSDR, RTL-SDR, SDRplay RSP1 and FunCube
 *
 * OpenAPI spec version: 4.0.0
 * Contact: f4exb06@gmail.com
 *
 * NOTE: This class is auto generated by the swagger code generator program.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * SWGChannel.h
 * 
 * Channel summarized information
 */

#ifndef SWGChannel_H_
#define SWGChannel_H_

#include <QJsonObject>


#include <QString>

#include "SWGObject.h"


namespace Swagger {

class SWGChannel: public SWGObject {
public:
    SWGChannel();
    SWGChannel(QString* json);
    virtual ~SWGChannel();
    void init();
    void cleanup();

    QString asJson ();
    QJsonObject* asJsonObject();
    void fromJsonObject(QJsonObject &json);
    SWGChannel* fromJson(QString &jsonString);

    qint32 getIndex();
    void setIndex(qint32 index);
QString* getId();
    void setId(QString* id);
qint32 getDeltaFrequency();
    void setDeltaFrequency(qint32 deltaFrequency);

private:
    qint32 index;
QString* id;
qint32 deltaFrequency;
};

} /* namespace Swagger */

#endif /* SWGChannel_H_ */

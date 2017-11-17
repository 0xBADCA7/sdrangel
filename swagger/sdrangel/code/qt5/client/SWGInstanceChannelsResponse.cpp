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


#include "SWGInstanceChannelsResponse.h"

#include "SWGHelpers.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include <QDebug>

namespace Swagger {


SWGInstanceChannelsResponse::SWGInstanceChannelsResponse(QString* json) {
    init();
    this->fromJson(*json);
}

SWGInstanceChannelsResponse::SWGInstanceChannelsResponse() {
    init();
}

SWGInstanceChannelsResponse::~SWGInstanceChannelsResponse() {
    this->cleanup();
}

void
SWGInstanceChannelsResponse::init() {
    channelcount = NULL;
channels = new QList<SWGChannelListItem*>();
}

void
SWGInstanceChannelsResponse::cleanup() {
    
if(channels != NULL) {
        QList<SWGChannelListItem*>* arr = channels;
        foreach(SWGChannelListItem* o, *arr) {
            delete o;
        }
        delete channels;
    }
}

SWGInstanceChannelsResponse*
SWGInstanceChannelsResponse::fromJson(QString &json) {
    QByteArray array (json.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
    return this;
}

void
SWGInstanceChannelsResponse::fromJsonObject(QJsonObject &pJson) {
    setValue(&channelcount, pJson["channelcount"], "qint32", "");
setValue(&channels, pJson["channels"], "QList", "SWGChannelListItem");
}

QString
SWGInstanceChannelsResponse::asJson ()
{
    QJsonObject* obj = this->asJsonObject();
    
    QJsonDocument doc(*obj);
    QByteArray bytes = doc.toJson();
    return QString(bytes);
}

QJsonObject*
SWGInstanceChannelsResponse::asJsonObject() {
    QJsonObject* obj = new QJsonObject();
    obj->insert("channelcount", QJsonValue(channelcount));

    
    QList<SWGChannelListItem*>* channelsList = channels;
    QJsonArray channelsJsonArray;
    toJsonArray((QList<void*>*)channels, &channelsJsonArray, "channels", "SWGChannelListItem");

    obj->insert("channels", channelsJsonArray);
    

    return obj;
}

qint32
SWGInstanceChannelsResponse::getChannelcount() {
    return channelcount;
}
void
SWGInstanceChannelsResponse::setChannelcount(qint32 channelcount) {
    this->channelcount = channelcount;
}

QList<SWGChannelListItem*>*
SWGInstanceChannelsResponse::getChannels() {
    return channels;
}
void
SWGInstanceChannelsResponse::setChannels(QList<SWGChannelListItem*>* channels) {
    this->channels = channels;
}



} /* namespace Swagger */


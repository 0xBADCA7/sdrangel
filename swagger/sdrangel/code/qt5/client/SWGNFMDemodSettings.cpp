/**
 * SDRangel
 * This is the web REST/JSON API of SDRangel SDR software. SDRangel is an Open Source Qt5/OpenGL 3.0+ (4.3+ in Windows) GUI and server Software Defined Radio and signal analyzer in software. It supports Airspy, BladeRF, HackRF, LimeSDR, PlutoSDR, RTL-SDR, SDRplay RSP1 and FunCube     ---   Limitations and specifcities:       * In SDRangel GUI the first Rx device set cannot be deleted. Conversely the server starts with no device sets and its number of device sets can be reduced to zero by as many calls as necessary to /sdrangel/deviceset with DELETE method.   * Stopping instance i.e. /sdrangel with DELETE method is a server only feature. It allows stopping the instance nicely.   * Preset import and export from/to file is a server only feature.   * Device set focus is a GUI only feature.   * The following channels are not implemented (status 501 is returned): ATV demodulator, Channel Analyzer, Channel Analyzer NG, LoRa demodulator, TCP source   * The content type returned is always application/json except in the following cases:     * An incorrect URL was specified: this document is returned as text/html with a status 400    --- 
 *
 * OpenAPI spec version: 4.0.0
 * Contact: f4exb06@gmail.com
 *
 * NOTE: This class is auto generated by the swagger code generator program.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */


#include "SWGNFMDemodSettings.h"

#include "SWGHelpers.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QObject>
#include <QDebug>

namespace SWGSDRangel {

SWGNFMDemodSettings::SWGNFMDemodSettings(QString* json) {
    init();
    this->fromJson(*json);
}

SWGNFMDemodSettings::SWGNFMDemodSettings() {
    input_frequency_offset = 0L;
    m_input_frequency_offset_isSet = false;
    rf_bandwidth = 0.0f;
    m_rf_bandwidth_isSet = false;
    af_bandwidth = 0.0f;
    m_af_bandwidth_isSet = false;
    fm_deviation = 0;
    m_fm_deviation_isSet = false;
    squelch_gate = 0;
    m_squelch_gate_isSet = false;
    delta_squelch = 0;
    m_delta_squelch_isSet = false;
    squelch = 0.0f;
    m_squelch_isSet = false;
    volume = 0.0f;
    m_volume_isSet = false;
    ctcss_on = 0;
    m_ctcss_on_isSet = false;
    audio_mute = 0;
    m_audio_mute_isSet = false;
    ctcss_index = 0;
    m_ctcss_index_isSet = false;
    rgb_color = 0;
    m_rgb_color_isSet = false;
    title = nullptr;
    m_title_isSet = false;
}

SWGNFMDemodSettings::~SWGNFMDemodSettings() {
    this->cleanup();
}

void
SWGNFMDemodSettings::init() {
    input_frequency_offset = 0L;
    m_input_frequency_offset_isSet = false;
    rf_bandwidth = 0.0f;
    m_rf_bandwidth_isSet = false;
    af_bandwidth = 0.0f;
    m_af_bandwidth_isSet = false;
    fm_deviation = 0;
    m_fm_deviation_isSet = false;
    squelch_gate = 0;
    m_squelch_gate_isSet = false;
    delta_squelch = 0;
    m_delta_squelch_isSet = false;
    squelch = 0.0f;
    m_squelch_isSet = false;
    volume = 0.0f;
    m_volume_isSet = false;
    ctcss_on = 0;
    m_ctcss_on_isSet = false;
    audio_mute = 0;
    m_audio_mute_isSet = false;
    ctcss_index = 0;
    m_ctcss_index_isSet = false;
    rgb_color = 0;
    m_rgb_color_isSet = false;
    title = new QString("");
    m_title_isSet = false;
}

void
SWGNFMDemodSettings::cleanup() {












    if(title != nullptr) { 
        delete title;
    }
}

SWGNFMDemodSettings*
SWGNFMDemodSettings::fromJson(QString &json) {
    QByteArray array (json.toStdString().c_str());
    QJsonDocument doc = QJsonDocument::fromJson(array);
    QJsonObject jsonObject = doc.object();
    this->fromJsonObject(jsonObject);
    return this;
}

void
SWGNFMDemodSettings::fromJsonObject(QJsonObject &pJson) {
    ::SWGSDRangel::setValue(&input_frequency_offset, pJson["inputFrequencyOffset"], "qint64", "");
    
    ::SWGSDRangel::setValue(&rf_bandwidth, pJson["rfBandwidth"], "float", "");
    
    ::SWGSDRangel::setValue(&af_bandwidth, pJson["afBandwidth"], "float", "");
    
    ::SWGSDRangel::setValue(&fm_deviation, pJson["fmDeviation"], "qint32", "");
    
    ::SWGSDRangel::setValue(&squelch_gate, pJson["squelchGate"], "qint32", "");
    
    ::SWGSDRangel::setValue(&delta_squelch, pJson["deltaSquelch"], "qint32", "");
    
    ::SWGSDRangel::setValue(&squelch, pJson["squelch"], "float", "");
    
    ::SWGSDRangel::setValue(&volume, pJson["volume"], "float", "");
    
    ::SWGSDRangel::setValue(&ctcss_on, pJson["ctcssOn"], "qint32", "");
    
    ::SWGSDRangel::setValue(&audio_mute, pJson["audioMute"], "qint32", "");
    
    ::SWGSDRangel::setValue(&ctcss_index, pJson["ctcssIndex"], "qint32", "");
    
    ::SWGSDRangel::setValue(&rgb_color, pJson["rgbColor"], "qint32", "");
    
    ::SWGSDRangel::setValue(&title, pJson["title"], "QString", "QString");
    
}

QString
SWGNFMDemodSettings::asJson ()
{
    QJsonObject* obj = this->asJsonObject();

    QJsonDocument doc(*obj);
    QByteArray bytes = doc.toJson();
    delete obj;
    return QString(bytes);
}

QJsonObject*
SWGNFMDemodSettings::asJsonObject() {
    QJsonObject* obj = new QJsonObject();
    if(m_input_frequency_offset_isSet){
        obj->insert("inputFrequencyOffset", QJsonValue(input_frequency_offset));
    }
    if(m_rf_bandwidth_isSet){
        obj->insert("rfBandwidth", QJsonValue(rf_bandwidth));
    }
    if(m_af_bandwidth_isSet){
        obj->insert("afBandwidth", QJsonValue(af_bandwidth));
    }
    if(m_fm_deviation_isSet){
        obj->insert("fmDeviation", QJsonValue(fm_deviation));
    }
    if(m_squelch_gate_isSet){
        obj->insert("squelchGate", QJsonValue(squelch_gate));
    }
    if(m_delta_squelch_isSet){
        obj->insert("deltaSquelch", QJsonValue(delta_squelch));
    }
    if(m_squelch_isSet){
        obj->insert("squelch", QJsonValue(squelch));
    }
    if(m_volume_isSet){
        obj->insert("volume", QJsonValue(volume));
    }
    if(m_ctcss_on_isSet){
        obj->insert("ctcssOn", QJsonValue(ctcss_on));
    }
    if(m_audio_mute_isSet){
        obj->insert("audioMute", QJsonValue(audio_mute));
    }
    if(m_ctcss_index_isSet){
        obj->insert("ctcssIndex", QJsonValue(ctcss_index));
    }
    if(m_rgb_color_isSet){
        obj->insert("rgbColor", QJsonValue(rgb_color));
    }
    if(title != nullptr && *title != QString("")){
        toJsonValue(QString("title"), title, obj, QString("QString"));
    }

    return obj;
}

qint64
SWGNFMDemodSettings::getInputFrequencyOffset() {
    return input_frequency_offset;
}
void
SWGNFMDemodSettings::setInputFrequencyOffset(qint64 input_frequency_offset) {
    this->input_frequency_offset = input_frequency_offset;
    this->m_input_frequency_offset_isSet = true;
}

float
SWGNFMDemodSettings::getRfBandwidth() {
    return rf_bandwidth;
}
void
SWGNFMDemodSettings::setRfBandwidth(float rf_bandwidth) {
    this->rf_bandwidth = rf_bandwidth;
    this->m_rf_bandwidth_isSet = true;
}

float
SWGNFMDemodSettings::getAfBandwidth() {
    return af_bandwidth;
}
void
SWGNFMDemodSettings::setAfBandwidth(float af_bandwidth) {
    this->af_bandwidth = af_bandwidth;
    this->m_af_bandwidth_isSet = true;
}

qint32
SWGNFMDemodSettings::getFmDeviation() {
    return fm_deviation;
}
void
SWGNFMDemodSettings::setFmDeviation(qint32 fm_deviation) {
    this->fm_deviation = fm_deviation;
    this->m_fm_deviation_isSet = true;
}

qint32
SWGNFMDemodSettings::getSquelchGate() {
    return squelch_gate;
}
void
SWGNFMDemodSettings::setSquelchGate(qint32 squelch_gate) {
    this->squelch_gate = squelch_gate;
    this->m_squelch_gate_isSet = true;
}

qint32
SWGNFMDemodSettings::getDeltaSquelch() {
    return delta_squelch;
}
void
SWGNFMDemodSettings::setDeltaSquelch(qint32 delta_squelch) {
    this->delta_squelch = delta_squelch;
    this->m_delta_squelch_isSet = true;
}

float
SWGNFMDemodSettings::getSquelch() {
    return squelch;
}
void
SWGNFMDemodSettings::setSquelch(float squelch) {
    this->squelch = squelch;
    this->m_squelch_isSet = true;
}

float
SWGNFMDemodSettings::getVolume() {
    return volume;
}
void
SWGNFMDemodSettings::setVolume(float volume) {
    this->volume = volume;
    this->m_volume_isSet = true;
}

qint32
SWGNFMDemodSettings::getCtcssOn() {
    return ctcss_on;
}
void
SWGNFMDemodSettings::setCtcssOn(qint32 ctcss_on) {
    this->ctcss_on = ctcss_on;
    this->m_ctcss_on_isSet = true;
}

qint32
SWGNFMDemodSettings::getAudioMute() {
    return audio_mute;
}
void
SWGNFMDemodSettings::setAudioMute(qint32 audio_mute) {
    this->audio_mute = audio_mute;
    this->m_audio_mute_isSet = true;
}

qint32
SWGNFMDemodSettings::getCtcssIndex() {
    return ctcss_index;
}
void
SWGNFMDemodSettings::setCtcssIndex(qint32 ctcss_index) {
    this->ctcss_index = ctcss_index;
    this->m_ctcss_index_isSet = true;
}

qint32
SWGNFMDemodSettings::getRgbColor() {
    return rgb_color;
}
void
SWGNFMDemodSettings::setRgbColor(qint32 rgb_color) {
    this->rgb_color = rgb_color;
    this->m_rgb_color_isSet = true;
}

QString*
SWGNFMDemodSettings::getTitle() {
    return title;
}
void
SWGNFMDemodSettings::setTitle(QString* title) {
    this->title = title;
    this->m_title_isSet = true;
}


bool
SWGNFMDemodSettings::isSet(){
    bool isObjectUpdated = false;
    do{
        if(m_input_frequency_offset_isSet){ isObjectUpdated = true; break;}
        if(m_rf_bandwidth_isSet){ isObjectUpdated = true; break;}
        if(m_af_bandwidth_isSet){ isObjectUpdated = true; break;}
        if(m_fm_deviation_isSet){ isObjectUpdated = true; break;}
        if(m_squelch_gate_isSet){ isObjectUpdated = true; break;}
        if(m_delta_squelch_isSet){ isObjectUpdated = true; break;}
        if(m_squelch_isSet){ isObjectUpdated = true; break;}
        if(m_volume_isSet){ isObjectUpdated = true; break;}
        if(m_ctcss_on_isSet){ isObjectUpdated = true; break;}
        if(m_audio_mute_isSet){ isObjectUpdated = true; break;}
        if(m_ctcss_index_isSet){ isObjectUpdated = true; break;}
        if(m_rgb_color_isSet){ isObjectUpdated = true; break;}
        if(title != nullptr && *title != QString("")){ isObjectUpdated = true; break;}
    }while(false);
    return isObjectUpdated;
}
}


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

/*
 * SWGNFMDemodSettings.h
 *
 * NFMDemod
 */

#ifndef SWGNFMDemodSettings_H_
#define SWGNFMDemodSettings_H_

#include <QJsonObject>


#include <QString>

#include "SWGObject.h"
#include "export.h"

namespace SWGSDRangel {

class SWG_API SWGNFMDemodSettings: public SWGObject {
public:
    SWGNFMDemodSettings();
    SWGNFMDemodSettings(QString* json);
    virtual ~SWGNFMDemodSettings();
    void init();
    void cleanup();

    virtual QString asJson () override;
    virtual QJsonObject* asJsonObject() override;
    virtual void fromJsonObject(QJsonObject &json) override;
    virtual SWGNFMDemodSettings* fromJson(QString &jsonString) override;

    qint64 getInputFrequencyOffset();
    void setInputFrequencyOffset(qint64 input_frequency_offset);

    float getRfBandwidth();
    void setRfBandwidth(float rf_bandwidth);

    float getAfBandwidth();
    void setAfBandwidth(float af_bandwidth);

    qint32 getFmDeviation();
    void setFmDeviation(qint32 fm_deviation);

    qint32 getSquelchGate();
    void setSquelchGate(qint32 squelch_gate);

    qint32 getDeltaSquelch();
    void setDeltaSquelch(qint32 delta_squelch);

    float getSquelch();
    void setSquelch(float squelch);

    float getVolume();
    void setVolume(float volume);

    qint32 getCtcssOn();
    void setCtcssOn(qint32 ctcss_on);

    qint32 getAudioMute();
    void setAudioMute(qint32 audio_mute);

    qint32 getCtcssIndex();
    void setCtcssIndex(qint32 ctcss_index);

    qint32 getRgbColor();
    void setRgbColor(qint32 rgb_color);

    QString* getTitle();
    void setTitle(QString* title);


    virtual bool isSet() override;

private:
    qint64 input_frequency_offset;
    bool m_input_frequency_offset_isSet;

    float rf_bandwidth;
    bool m_rf_bandwidth_isSet;

    float af_bandwidth;
    bool m_af_bandwidth_isSet;

    qint32 fm_deviation;
    bool m_fm_deviation_isSet;

    qint32 squelch_gate;
    bool m_squelch_gate_isSet;

    qint32 delta_squelch;
    bool m_delta_squelch_isSet;

    float squelch;
    bool m_squelch_isSet;

    float volume;
    bool m_volume_isSet;

    qint32 ctcss_on;
    bool m_ctcss_on_isSet;

    qint32 audio_mute;
    bool m_audio_mute_isSet;

    qint32 ctcss_index;
    bool m_ctcss_index_isSet;

    qint32 rgb_color;
    bool m_rgb_color_isSet;

    QString* title;
    bool m_title_isSet;

};

}

#endif /* SWGNFMDemodSettings_H_ */

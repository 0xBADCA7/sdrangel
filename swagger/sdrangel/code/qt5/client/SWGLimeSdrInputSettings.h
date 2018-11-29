/**
 * SDRangel
 * This is the web REST/JSON API of SDRangel SDR software. SDRangel is an Open Source Qt5/OpenGL 3.0+ (4.3+ in Windows) GUI and server Software Defined Radio and signal analyzer in software. It supports Airspy, BladeRF, HackRF, LimeSDR, PlutoSDR, RTL-SDR, SDRplay RSP1 and FunCube    ---   Limitations and specifcities:    * In SDRangel GUI the first Rx device set cannot be deleted. Conversely the server starts with no device sets and its number of device sets can be reduced to zero by as many calls as necessary to /sdrangel/deviceset with DELETE method.   * Preset import and export from/to file is a server only feature.   * Device set focus is a GUI only feature.   * The following channels are not implemented (status 501 is returned): ATV and DATV demodulators, Channel Analyzer NG, LoRa demodulator   * The device settings and report structures contains only the sub-structure corresponding to the device type. The DeviceSettings and DeviceReport structures documented here shows all of them but only one will be or should be present at a time   * The channel settings and report structures contains only the sub-structure corresponding to the channel type. The ChannelSettings and ChannelReport structures documented here shows all of them but only one will be or should be present at a time    --- 
 *
 * OpenAPI spec version: 4.3.0
 * Contact: f4exb06@gmail.com
 *
 * NOTE: This class is auto generated by the swagger code generator program.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */

/*
 * SWGLimeSdrInputSettings.h
 *
 * LimeSDR
 */

#ifndef SWGLimeSdrInputSettings_H_
#define SWGLimeSdrInputSettings_H_

#include <QJsonObject>


#include <QString>

#include "SWGObject.h"
#include "export.h"

namespace SWGSDRangel {

class SWG_API SWGLimeSdrInputSettings: public SWGObject {
public:
    SWGLimeSdrInputSettings();
    SWGLimeSdrInputSettings(QString* json);
    virtual ~SWGLimeSdrInputSettings();
    void init();
    void cleanup();

    virtual QString asJson () override;
    virtual QJsonObject* asJsonObject() override;
    virtual void fromJsonObject(QJsonObject &json) override;
    virtual SWGLimeSdrInputSettings* fromJson(QString &jsonString) override;

    qint64 getCenterFrequency();
    void setCenterFrequency(qint64 center_frequency);

    qint32 getDevSampleRate();
    void setDevSampleRate(qint32 dev_sample_rate);

    qint32 getLog2HardDecim();
    void setLog2HardDecim(qint32 log2_hard_decim);

    qint32 getDcBlock();
    void setDcBlock(qint32 dc_block);

    qint32 getIqCorrection();
    void setIqCorrection(qint32 iq_correction);

    qint32 getLog2SoftDecim();
    void setLog2SoftDecim(qint32 log2_soft_decim);

    qint32 getLpfBw();
    void setLpfBw(qint32 lpf_bw);

    qint32 getLpfFirEnable();
    void setLpfFirEnable(qint32 lpf_fir_enable);

    qint32 getLpfFirbw();
    void setLpfFirbw(qint32 lpf_firbw);

    qint32 getGain();
    void setGain(qint32 gain);

    qint32 getNcoEnable();
    void setNcoEnable(qint32 nco_enable);

    qint32 getNcoFrequency();
    void setNcoFrequency(qint32 nco_frequency);

    qint32 getAntennaPath();
    void setAntennaPath(qint32 antenna_path);

    qint32 getGainMode();
    void setGainMode(qint32 gain_mode);

    qint32 getLnaGain();
    void setLnaGain(qint32 lna_gain);

    qint32 getTiaGain();
    void setTiaGain(qint32 tia_gain);

    qint32 getPgaGain();
    void setPgaGain(qint32 pga_gain);

    qint32 getExtClock();
    void setExtClock(qint32 ext_clock);

    qint32 getExtClockFreq();
    void setExtClockFreq(qint32 ext_clock_freq);

    qint32 getTransverterMode();
    void setTransverterMode(qint32 transverter_mode);

    qint64 getTransverterDeltaFrequency();
    void setTransverterDeltaFrequency(qint64 transverter_delta_frequency);

    QString* getFileRecordName();
    void setFileRecordName(QString* file_record_name);

    qint32 getGpioDir();
    void setGpioDir(qint32 gpio_dir);

    qint32 getGpioPins();
    void setGpioPins(qint32 gpio_pins);


    virtual bool isSet() override;

private:
    qint64 center_frequency;
    bool m_center_frequency_isSet;

    qint32 dev_sample_rate;
    bool m_dev_sample_rate_isSet;

    qint32 log2_hard_decim;
    bool m_log2_hard_decim_isSet;

    qint32 dc_block;
    bool m_dc_block_isSet;

    qint32 iq_correction;
    bool m_iq_correction_isSet;

    qint32 log2_soft_decim;
    bool m_log2_soft_decim_isSet;

    qint32 lpf_bw;
    bool m_lpf_bw_isSet;

    qint32 lpf_fir_enable;
    bool m_lpf_fir_enable_isSet;

    qint32 lpf_firbw;
    bool m_lpf_firbw_isSet;

    qint32 gain;
    bool m_gain_isSet;

    qint32 nco_enable;
    bool m_nco_enable_isSet;

    qint32 nco_frequency;
    bool m_nco_frequency_isSet;

    qint32 antenna_path;
    bool m_antenna_path_isSet;

    qint32 gain_mode;
    bool m_gain_mode_isSet;

    qint32 lna_gain;
    bool m_lna_gain_isSet;

    qint32 tia_gain;
    bool m_tia_gain_isSet;

    qint32 pga_gain;
    bool m_pga_gain_isSet;

    qint32 ext_clock;
    bool m_ext_clock_isSet;

    qint32 ext_clock_freq;
    bool m_ext_clock_freq_isSet;

    qint32 transverter_mode;
    bool m_transverter_mode_isSet;

    qint64 transverter_delta_frequency;
    bool m_transverter_delta_frequency_isSet;

    QString* file_record_name;
    bool m_file_record_name_isSet;

    qint32 gpio_dir;
    bool m_gpio_dir_isSet;

    qint32 gpio_pins;
    bool m_gpio_pins_isSet;

};

}

#endif /* SWGLimeSdrInputSettings_H_ */

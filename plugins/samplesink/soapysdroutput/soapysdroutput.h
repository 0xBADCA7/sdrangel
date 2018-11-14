///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2018 Edouard Griffiths, F4EXB                                   //
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

#ifndef PLUGINS_SAMPLESINK_SOAPYSDROUTPUT_SOAPYSDROUTPUT_H_
#define PLUGINS_SAMPLESINK_SOAPYSDROUTPUT_SOAPYSDROUTPUT_H_

#include <QString>
#include <QByteArray>
#include <stdint.h>

#include "dsp/devicesamplesink.h"
#include "soapysdr/devicesoapysdrshared.h"

#include "soapysdroutputsettings.h"

class DeviceSinkAPI;
class SoapySDROutputThread;

namespace SoapySDR
{
    class Device;
    class ArgInfo;
}

namespace SWGSDRangel
{
    class SWGArgValue;
    class SWGArgInfo;
}

class SoapySDROutput : public DeviceSampleSink {
public:
    class MsgConfigureSoapySDROutput : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        const SoapySDROutputSettings& getSettings() const { return m_settings; }
        bool getForce() const { return m_force; }

        static MsgConfigureSoapySDROutput* create(const SoapySDROutputSettings& settings, bool force)
        {
            return new MsgConfigureSoapySDROutput(settings, force);
        }

    private:
        SoapySDROutputSettings m_settings;
        bool m_force;

        MsgConfigureSoapySDROutput(const SoapySDROutputSettings& settings, bool force) :
            Message(),
            m_settings(settings),
            m_force(force)
        { }
    };

    class MsgReportGainChange : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        const SoapySDROutputSettings& getSettings() const { return m_settings; }
        bool getGlobalGain() const { return m_globalGain; }
        bool getIndividualGains() const { return m_individualGains; }

        static MsgReportGainChange* create(const SoapySDROutputSettings& settings, bool globalGain, bool individualGains)
        {
            return new MsgReportGainChange(settings, globalGain, individualGains);
        }

    private:
        SoapySDROutputSettings m_settings;
        bool m_globalGain;
        bool m_individualGains;

        MsgReportGainChange(const SoapySDROutputSettings& settings, bool globalGain, bool individualGains) :
            Message(),
            m_settings(settings),
            m_globalGain(globalGain),
            m_individualGains(individualGains)
        { }
    };

    class MsgStartStop : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        bool getStartStop() const { return m_startStop; }

        static MsgStartStop* create(bool startStop) {
            return new MsgStartStop(startStop);
        }

    protected:
        bool m_startStop;

        MsgStartStop(bool startStop) :
            Message(),
            m_startStop(startStop)
        { }
    };

    SoapySDROutput(DeviceSinkAPI *deviceAPI);
    virtual ~SoapySDROutput();
    virtual void destroy();

    virtual void init();
    virtual bool start();
    virtual void stop();
    SoapySDROutputThread *getThread() { return m_thread; }
    void setThread(SoapySDROutputThread *thread) { m_thread = thread; }

    virtual QByteArray serialize() const;
    virtual bool deserialize(const QByteArray& data);

    virtual void setMessageQueueToGUI(MessageQueue *queue) { m_guiMessageQueue = queue; }
    virtual const QString& getDeviceDescription() const;
    virtual int getSampleRate() const;
    virtual quint64 getCenterFrequency() const;
    virtual void setCenterFrequency(qint64 centerFrequency);

    virtual bool handleMessage(const Message& message);

    void getFrequencyRange(uint64_t& min, uint64_t& max);
    void getGlobalGainRange(int& min, int& max);
    bool isAGCSupported();
    const SoapySDR::RangeList& getRateRanges();
    const std::vector<std::string>& getAntennas();
    const SoapySDR::RangeList& getBandwidthRanges();
    const std::vector<DeviceSoapySDRParams::FrequencySetting>& getTunableElements();
    const std::vector<DeviceSoapySDRParams::GainSetting>& getIndividualGainsRanges();
    const SoapySDR::ArgInfoList& getStreamArgInfoList();
    const SoapySDR::ArgInfoList& getDeviceArgInfoList();
    void initGainSettings(SoapySDROutputSettings& settings);
    void initStreamArgSettings(SoapySDROutputSettings& settings);
    void initDeviceArgSettings(SoapySDROutputSettings& settings);
    bool hasDCAutoCorrection();
    bool hasDCCorrectionValue();
    bool hasIQAutoCorrection() { return false; } // not in SoapySDR interface
    bool hasIQCorrectionValue();

    virtual int webapiSettingsGet(
                SWGSDRangel::SWGDeviceSettings& response,
                QString& errorMessage);

    virtual int webapiSettingsPutPatch(
                bool force,
                const QStringList& deviceSettingsKeys,
                SWGSDRangel::SWGDeviceSettings& response, // query + response
                QString& errorMessage);

    virtual int webapiReportGet(
            SWGSDRangel::SWGDeviceReport& response,
            QString& errorMessage);

    virtual int webapiRunGet(
            SWGSDRangel::SWGDeviceState& response,
            QString& errorMessage);

    virtual int webapiRun(
            bool run,
            SWGSDRangel::SWGDeviceState& response,
            QString& errorMessage);

private:
    DeviceSinkAPI *m_deviceAPI;
    QMutex m_mutex;
    SoapySDROutputSettings m_settings;
    QString m_deviceDescription;
    bool m_running;
    SoapySDROutputThread *m_thread;
    DeviceSoapySDRShared m_deviceShared;

    bool openDevice();
    void closeDevice();
    SoapySDROutputThread *findThread();
    void moveThreadToBuddy();
    bool applySettings(const SoapySDROutputSettings& settings, bool force = false);
    bool setDeviceCenterFrequency(SoapySDR::Device *dev, int requestedChannel, quint64 freq_hz, int loPpmTenths);
    void updateGains(SoapySDR::Device *dev, int requestedChannel, SoapySDROutputSettings& settings);
    void webapiFormatDeviceSettings(SWGSDRangel::SWGDeviceSettings& response, const SoapySDROutputSettings& settings);
    void webapiFormatDeviceReport(SWGSDRangel::SWGDeviceReport& response);
    void webapiFormatArgValue(const QVariant& v, SWGSDRangel::SWGArgValue *argValue);
    void webapiFormatArgInfo(const SoapySDR::ArgInfo& arg, SWGSDRangel::SWGArgInfo *argInfo);
};


#endif /* PLUGINS_SAMPLESINK_SOAPYSDROUTPUT_SOAPYSDROUTPUT_H_ */

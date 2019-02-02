///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2018-2019 Edouard Griffiths, F4EXB                              //
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

#ifndef PLUGINS_CHANNELTX_REMOTESRC_REMOTESRC_H_
#define PLUGINS_CHANNELTX_REMOTESRC_REMOTESRC_H_

#include <channel/remotedatablock.h>
#include <channel/remotedataqueue.h>
#include <channel/remotedatareadqueue.h>
#include <QObject>
#include <QNetworkRequest>

#include "cm256.h"

#include "dsp/basebandsamplesource.h"
#include "channel/channelsourceapi.h"
#include "util/message.h"

#include "../remotesource/remotesourcesettings.h"

class ThreadedBasebandSampleSource;
class UpChannelizer;
class DeviceSinkAPI;
class RemoteSourceThread;
class RemoteDataBlock;
class QNetworkAccessManager;
class QNetworkReply;

class RemoteSource : public BasebandSampleSource, public ChannelSourceAPI {
    Q_OBJECT

public:
    class MsgConfigureRemoteSource : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        const RemoteSourceSettings& getSettings() const { return m_settings; }
        bool getForce() const { return m_force; }

        static MsgConfigureRemoteSource* create(const RemoteSourceSettings& settings, bool force)
        {
            return new MsgConfigureRemoteSource(settings, force);
        }

    private:
        RemoteSourceSettings m_settings;
        bool m_force;

        MsgConfigureRemoteSource(const RemoteSourceSettings& settings, bool force) :
            Message(),
            m_settings(settings),
            m_force(force)
        { }
    };

    class MsgSampleRateNotification : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        static MsgSampleRateNotification* create(int sampleRate) {
            return new MsgSampleRateNotification(sampleRate);
        }

        int getSampleRate() const { return m_sampleRate; }

    private:

        MsgSampleRateNotification(int sampleRate) :
            Message(),
            m_sampleRate(sampleRate)
        { }

        int m_sampleRate;
    };

    class MsgQueryStreamData : public Message {
        MESSAGE_CLASS_DECLARATION
    public:
        static MsgQueryStreamData* create() {
            return new MsgQueryStreamData();
        }
    private:
        MsgQueryStreamData() : Message() {}
    };

    class MsgReportStreamData : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        uint32_t get_tv_sec() const { return m_tv_sec; }
        uint32_t get_tv_usec() const { return m_tv_usec; }
        uint32_t get_queueSize() const { return m_queueSize; }
        uint32_t get_queueLength() const { return m_queueLength; }
        uint32_t get_readSamplesCount() const { return m_readSamplesCount; }
        uint32_t get_nbCorrectableErrors() const { return m_nbCorrectableErrors; }
        uint32_t get_nbUncorrectableErrors() const { return m_nbUncorrectableErrors; }
        uint32_t get_nbOriginalBlocks() const { return m_nbOriginalBlocks; }
        uint32_t get_nbFECBlocks() const { return m_nbFECBlocks; }
        uint32_t get_centerFreq() const { return m_centerFreq; }
        uint32_t get_sampleRate() const { return m_sampleRate; }

        static MsgReportStreamData* create(
                uint32_t tv_sec,
                uint32_t tv_usec,
                uint32_t queueSize,
                uint32_t queueLength,
                uint32_t readSamplesCount,
                uint32_t nbCorrectableErrors,
                uint32_t nbUncorrectableErrors,
                uint32_t nbOriginalBlocks,
                uint32_t nbFECBlocks,
                uint32_t centerFreq,
                uint32_t sampleRate)
        {
            return new MsgReportStreamData(
                    tv_sec,
                    tv_usec,
                    queueSize,
                    queueLength,
                    readSamplesCount,
                    nbCorrectableErrors,
                    nbUncorrectableErrors,
                    nbOriginalBlocks,
                    nbFECBlocks,
                    centerFreq,
                    sampleRate);
        }

    protected:
        uint32_t m_tv_sec;
        uint32_t m_tv_usec;
        uint32_t m_queueSize;
        uint32_t m_queueLength;
        uint32_t m_readSamplesCount;
        uint32_t m_nbCorrectableErrors;
        uint32_t m_nbUncorrectableErrors;
        uint32_t m_nbOriginalBlocks;
        uint32_t m_nbFECBlocks;
        uint32_t m_centerFreq;
        uint32_t m_sampleRate;

        MsgReportStreamData(
                uint32_t tv_sec,
                uint32_t tv_usec,
                uint32_t queueSize,
                uint32_t queueLength,
                uint32_t readSamplesCount,
                uint32_t nbCorrectableErrors,
                uint32_t nbUncorrectableErrors,
                uint32_t nbOriginalBlocks,
                uint32_t nbFECBlocks,
                uint32_t centerFreq,
                uint32_t sampleRate) :
            Message(),
            m_tv_sec(tv_sec),
            m_tv_usec(tv_usec),
            m_queueSize(queueSize),
            m_queueLength(queueLength),
            m_readSamplesCount(readSamplesCount),
            m_nbCorrectableErrors(nbCorrectableErrors),
            m_nbUncorrectableErrors(nbUncorrectableErrors),
            m_nbOriginalBlocks(nbOriginalBlocks),
            m_nbFECBlocks(nbFECBlocks),
            m_centerFreq(centerFreq),
            m_sampleRate(sampleRate)
        { }
    };

    RemoteSource(DeviceSinkAPI *deviceAPI);
    ~RemoteSource();

    virtual void destroy() { delete this; }

    virtual void pull(Sample& sample);
    virtual void pullAudio(int nbSamples);
    virtual void start();
    virtual void stop();
    virtual bool handleMessage(const Message& cmd);

    virtual void getIdentifier(QString& id) { id = objectName(); }
    virtual void getTitle(QString& title) { title = m_settings.m_title; }
    virtual qint64 getCenterFrequency() const { return 0; }

    virtual QByteArray serialize() const;
    virtual bool deserialize(const QByteArray& data);

    virtual int webapiSettingsGet(
            SWGSDRangel::SWGChannelSettings& response,
            QString& errorMessage);

    virtual int webapiSettingsPutPatch(
            bool force,
            const QStringList& channelSettingsKeys,
            SWGSDRangel::SWGChannelSettings& response,
            QString& errorMessage);

    virtual int webapiReportGet(
            SWGSDRangel::SWGChannelReport& response,
            QString& errorMessage);

    void setDataLink(const QString& dataAddress, uint16_t dataPort);

    static const QString m_channelIdURI;
    static const QString m_channelId;

private:
    DeviceSinkAPI* m_deviceAPI;
    ThreadedBasebandSampleSource* m_threadedChannelizer;
    UpChannelizer* m_channelizer;
    RemoteDataQueue m_dataQueue;
    RemoteSourceThread *m_sourceThread;
    CM256 m_cm256;
    CM256 *m_cm256p;
    bool m_running;

    RemoteSourceSettings m_settings;

    CM256::cm256_block   m_cm256DescriptorBlocks[2*RemoteNbOrginalBlocks]; //!< CM256 decoder descriptors (block addresses and block indexes)
    RemoteMetaDataFEC m_currentMeta;

    RemoteDataReadQueue m_dataReadQueue;

    uint32_t m_nbCorrectableErrors;   //!< count of correctable errors in number of blocks
    uint32_t m_nbUncorrectableErrors; //!< count of uncorrectable errors in number of blocks

    QNetworkAccessManager *m_networkManager;
    QNetworkRequest m_networkRequest;

    void applySettings(const RemoteSourceSettings& settings, bool force = false);
    void handleDataBlock(RemoteDataBlock *dataBlock);
    void printMeta(const QString& header, RemoteMetaDataFEC *metaData);
    uint32_t calculateDataReadQueueSize(int sampleRate);
    void webapiFormatChannelSettings(SWGSDRangel::SWGChannelSettings& response, const RemoteSourceSettings& settings);
    void webapiFormatChannelReport(SWGSDRangel::SWGChannelReport& response);
    void webapiReverseSendSettings(QList<QString>& channelSettingsKeys, const RemoteSourceSettings& settings, bool force);

private slots:
    void networkManagerFinished(QNetworkReply *reply);
    void handleData();
};

#endif // PLUGINS_CHANNELTX_REMOTESRC_REMOTESRC_H_

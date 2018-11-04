///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2015 Edouard Griffiths, F4EXB                                   //
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

#ifndef PLUGINS_SAMPLESINK_SOAPYSDROUTPUT_SOAPYSDROUTPUTTHREAD_H_
#define PLUGINS_SAMPLESINK_SOAPYSDROUTPUT_SOAPYSDROUTPUTTHREAD_H_


#include <QThread>
#include <QMutex>
#include <QWaitCondition>

#include <SoapySDR/Device.hpp>

#include "soapysdr/devicesoapysdrshared.h"
#include "dsp/interpolators.h"

class SampleSourceFifo;

class SoapySDROutputThread : public QThread {
    Q_OBJECT

public:
    SoapySDROutputThread(SoapySDR::Device* dev, unsigned int nbTxChannels, QObject* parent = 0);
    ~SoapySDROutputThread();

    void startWork();
    void stopWork();
    bool isRunning() const { return m_running; }
    unsigned int getNbChannels() const { return m_nbChannels; }
    void setLog2Interpolation(unsigned int channel, unsigned int log2_interp);
    unsigned int getLog2Interpolation(unsigned int channel) const;
    void setFifo(unsigned int channel, SampleSourceFifo *sampleFifo);
    SampleSourceFifo *getFifo(unsigned int channel);

private:
    struct Channel
    {
        SampleSourceFifo* m_sampleFifo;
        unsigned int m_log2Interp;
        Interpolators<qint8, SDR_TX_SAMP_SZ, 8> m_interpolators8;
        Interpolators<qint16, SDR_TX_SAMP_SZ, 12> m_interpolators12;
        Interpolators<qint16, SDR_TX_SAMP_SZ, 16> m_interpolators16;

        Channel() :
            m_sampleFifo(0),
            m_log2Interp(0)
        {}

        ~Channel()
        {}
    };

    enum InterpolatorType
    {
        Interpolator8,
        Interpolator12,
        Interpolator16,
        InterpolatorFloat
    };


    QMutex m_startWaitMutex;
    QWaitCondition m_startWaiter;
    bool m_running;
    SoapySDR::Device* m_dev;

    Channel *m_channels; //!< Array of channels dynamically allocated for the given number of Tx channels
    unsigned int m_sampleRate;
    unsigned int m_nbChannels;
    InterpolatorType m_interpolatorType;

    void run();
    unsigned int getNbFifos();
    void callbackSO8(qint8* buf, qint32 len, unsigned int channel = 0);
    void callbackSO12(qint16* buf, qint32 len, unsigned int channel = 0);
    void callbackSO16(qint16* buf, qint32 len, unsigned int channel = 0);
    void callbackMO(std::vector<void *>& buffs, qint32 samplesPerChannel);
};


#endif /* PLUGINS_SAMPLESINK_SOAPYSDROUTPUT_SOAPYSDROUTPUTTHREAD_H_ */

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

#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <algorithm>
#include <QDebug>

#include "dsp/samplesourcefifo.h"
#include "sdrdaemonsinkthread.h"

SDRdaemonSinkThread::SDRdaemonSinkThread(SampleSourceFifo* sampleFifo, QObject* parent) :
	QThread(parent),
	m_running(false),
	m_samplesChunkSize(0),
	m_sampleFifo(sampleFifo),
	m_samplesCount(0),
    m_samplerate(0),
    m_throttlems(SDRDAEMONSINK_THROTTLE_MS),
    m_throttleToggle(false),
    m_maxThrottlems(50)
{
}

SDRdaemonSinkThread::~SDRdaemonSinkThread()
{
	if (m_running) {
		stopWork();
	}
}

void SDRdaemonSinkThread::startWork()
{
	qDebug() << "SDRdaemonSinkThread::startWork: ";
    m_maxThrottlems = 0;
    m_startWaitMutex.lock();
    m_elapsedTimer.start();
    start();
    while(!m_running)
        m_startWaiter.wait(&m_startWaitMutex, 100);
    m_startWaitMutex.unlock();
}

void SDRdaemonSinkThread::stopWork()
{
	qDebug() << "SDRdaemonSinkThread::stopWork";
	m_running = false;
	wait();
}

void SDRdaemonSinkThread::setSamplerate(int samplerate)
{
	if (samplerate != m_samplerate)
	{
	    qDebug() << "SDRdaemonSinkThread::setSamplerate:"
	            << " new:" << samplerate
	            << " old:" << m_samplerate;

	    bool wasRunning = false;

		if (m_running)
		{
			stopWork();
			wasRunning = true;
		}

		// resize sample FIFO
		if (m_sampleFifo) {
		    m_sampleFifo->resize(samplerate); // 1s buffer
		}

        m_samplerate = samplerate;
        m_samplesChunkSize = (m_samplerate * m_throttlems) / 1000;

        if (wasRunning) {
            startWork();
        }
	}
}

void SDRdaemonSinkThread::run()
{
	int res;

	m_running = true;
	m_startWaiter.wakeAll();

	while(m_running) // actual work is in the tick() function
	{
		sleep(1);
	}

	m_running = false;
}

void SDRdaemonSinkThread::connectTimer(const QTimer& timer)
{
	qDebug() << "SDRdaemonSinkThread::connectTimer";
	connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
}

void SDRdaemonSinkThread::tick()
{
	if (m_running)
	{
        qint64 throttlems = m_elapsedTimer.restart();

        if (throttlems != m_throttlems)
        {
            m_throttlems = throttlems;
            m_samplesChunkSize = (m_samplerate * (m_throttlems+(m_throttleToggle ? 1 : 0))) / 1000;
            m_throttleToggle = !m_throttleToggle;
        }

//        if (m_throttlems > m_maxThrottlems)
//        {
//            qDebug("FileSinkThread::tick: m_maxThrottlems: %d", m_maxThrottlems);
//            m_maxThrottlems = m_throttlems;
//        }

        SampleVector::iterator readUntil;

        m_sampleFifo->readAdvance(readUntil, m_samplesChunkSize); // pull samples
        SampleVector::iterator beginRead = readUntil - m_samplesChunkSize;
        m_samplesCount += m_samplesChunkSize;

        m_udpSinkFEC.write(beginRead, m_samplesChunkSize);
//        m_ofstream->write(reinterpret_cast<char*>(&(*beginRead)), m_samplesChunkSize*sizeof(Sample)); // send samples

        // interpolation is done on the far side
//        if (m_log2Interpolation == 0)
//        {
//            m_ofstream->write(reinterpret_cast<char*>(&(*beginRead)), m_samplesChunkSize*sizeof(Sample)); // send samples
//        }
//        else
//        {
//            int chunkSize = std::min((int) m_samplesChunkSize, m_samplerate);
//
//            switch (m_log2Interpolation)
//            {
//            case 1:
//                m_interpolators.interpolate2_cen(&beginRead, m_buf, chunkSize*(1<<m_log2Interpolation)*2);
//                break;
//            case 2:
//                m_interpolators.interpolate4_cen(&beginRead, m_buf, chunkSize*(1<<m_log2Interpolation)*2);
//                break;
//            case 3:
//                m_interpolators.interpolate8_cen(&beginRead, m_buf, chunkSize*(1<<m_log2Interpolation)*2);
//                break;
//            case 4:
//                m_interpolators.interpolate16_cen(&beginRead, m_buf, chunkSize*(1<<m_log2Interpolation)*2);
//                break;
//            case 5:
//                m_interpolators.interpolate32_cen(&beginRead, m_buf, chunkSize*(1<<m_log2Interpolation)*2);
//                break;
//            case 6:
//                m_interpolators.interpolate64_cen(&beginRead, m_buf, chunkSize*(1<<m_log2Interpolation)*2);
//                break;
//            default:
//                break;
//            }
//
//            m_ofstream->write(reinterpret_cast<char*>(m_buf), m_samplesChunkSize*(1<<m_log2Interpolation)*2*sizeof(int16_t)); // send samples
//        }

	}
}

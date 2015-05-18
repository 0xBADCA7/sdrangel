///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2012 maintech GmbH, Otto-Hahn-Str. 15, 97204 Hoechberg, Germany //
// written by Christian Daniel                                                   //
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

#include <string.h>
#include <errno.h>
#include "v4linput.h"
#include "v4lthread.h"
#include "v4lgui.h"
#include "util/simpleserializer.h"

MESSAGE_CLASS_DEFINITION(V4LInput::MsgConfigureV4L, Message)
MESSAGE_CLASS_DEFINITION(V4LInput::MsgReportV4L, Message)

V4LInput::Settings::Settings() :
	m_gain(0)
{
}

void V4LInput::Settings::resetToDefaults()
{
	m_gain = 0;
}

QByteArray V4LInput::Settings::serialize() const
{
	SimpleSerializer s(1);
	s.writeS32(1, m_gain);
	s.writeS32(2, SAMPLERATE);
	return s.final();
}

bool V4LInput::Settings::deserialize(const QByteArray& data)
{
	SimpleDeserializer d(data);

	if(!d.isValid()) {
		resetToDefaults();
		return false;
	}

	if(d.getVersion() == 1) {
		d.readS32(1, &m_gain, 0);
		//d.readS32(2, &m_samplerate, 0);
		return true;
	} else {
		resetToDefaults();
		return false;
	}
}

V4LInput::V4LInput(MessageQueue* msgQueueToGUI) :
	SampleSource(msgQueueToGUI),
	m_settings(),
	m_V4LThread(NULL),
	m_deviceDescription()
{
}

V4LInput::~V4LInput()
{
	stopInput();
}

bool V4LInput::startInput(int device)
{
	QMutexLocker mutexLocker(&m_mutex);
	double freq;

	if(m_V4LThread)
		return false;

	if(!m_sampleFifo.setSize(4096*16)) {
		qCritical("Could not allocate SampleFifo");
		return false;
	}

	freq = (double)getCenterFrequency();
	if((m_V4LThread = new V4LThread(&m_sampleFifo, freq)) == NULL) {
		qFatal("out of memory");
		return false;
	}

	m_deviceDescription = QString("SDRplay /dev/swradio0");

	qDebug("V4LInput: start");
	//MsgReportV4L::create(m_gains)->submit(m_guiMessageQueue);

	return true;
}

void V4LInput::stopInput()
{
	QMutexLocker mutexLocker(&m_mutex);

	if(m_V4LThread) {
		m_V4LThread->stopWork();
		// wait for thread to quit ?
		delete m_V4LThread;
		m_V4LThread = NULL;
	}
	m_deviceDescription.clear();
}

const QString& V4LInput::getDeviceDescription() const
{
	return m_deviceDescription;
}

int V4LInput::getSampleRate() const
{
	// The output rate is lower than the device rate
	int result = SAMPLERATE / 4;
	return result;
}

quint64 V4LInput::getCenterFrequency() const
{
	return m_generalSettings.m_centerFrequency;
}

bool V4LInput::handleMessage(Message* message)
{
	if(MsgConfigureV4L::match(message)) {
		MsgConfigureV4L* conf = (MsgConfigureV4L*)message;
		applySettings(conf->getGeneralSettings(), conf->getSettings(), false);
		message->completed();
		return true;
	} else {
		return false;
	}
}

void V4LInput::applySettings(const GeneralSettings& generalSettings, const Settings& settings, bool force)
{
	QMutexLocker mutexLocker(&m_mutex);

	if (!m_V4LThread) {
			m_generalSettings.m_centerFrequency = generalSettings.m_centerFrequency;
			return;
	}

	if((m_generalSettings.m_centerFrequency != generalSettings.m_centerFrequency) || force) {
		m_V4LThread->set_center_freq( (double)generalSettings.m_centerFrequency );
	}
	m_generalSettings.m_centerFrequency = generalSettings.m_centerFrequency;
#if 0
	if((m_settings.m_gain != settings.m_gain) || force) {
		m_settings.m_gain = settings.m_gain;
		m_V4LThread->set_tuner_gain((double)m_settings.m_gain);
	}
#endif
}


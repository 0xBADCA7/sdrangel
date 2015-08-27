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

#include <stdio.h>
#include <errno.h>
#include "v4lthread.h"
#include "dsp/samplefifo.h"

V4LThread::V4LThread(SampleFifo* sampleFifo, double frequency, QObject* parent) :
	QThread(parent),
	m_running(false),
	m_convertBuffer(FCD_BLOCKSIZE),
	m_sampleFifo(sampleFifo)
{
	centerFreq = frequency;
	start();
}

V4LThread::~V4LThread()
{
}

void V4LThread::stopWork()
{
	m_running = false;
	wait();
}

void V4LThread::run()
{
	m_running = true;
	OpenSource("/dev/swradio0");
	if (fd < 0)
                return;

	while(m_running) {
		work(FCD_BLOCKSIZE);
	}
	CloseSource();
}


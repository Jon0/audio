/*
 * BaseBuffer.cpp
 *
 *  Created on: 9/08/2013
 *      Author: remnanjona
 */

#define maxblocks 5
#define minblocks 1

#include <chrono>
#include <iostream>
#include <sys/time.h>
#include "BaseBuffer.h"

namespace std {

BaseBuffer::BaseBuffer(): m_stop(true), m_thread(), data() {
	blocksize = 512; //1024*32;
	m_size = 0;
	current = NULL;
	current_start = 0;
}

BaseBuffer::~BaseBuffer() {
	try { stop(); } catch(...) {
		/*??*/
	}
}

int BaseBuffer::getFormat() {
	return 0;
}

void BaseBuffer::stop() {
	cout << "stop" << endl;
	data_mutex.lock();
	m_stop = true;
	data_mutex.unlock();
}

long BaseBuffer::available() {
	return blocksize;
}

void *BaseBuffer::next() {

	// start producing blocks if number is below threshold
	if (m_stop.load() && m_size.load() < minblocks) {

		data_mutex.lock();
		m_stop = false;
		cout << "start" << endl;
		if (m_thread.joinable()) {
			m_thread.join();
		}
		m_thread = thread(&BaseBuffer::makeBlocks, this);
		data_mutex.unlock();
	}

	// prevent null return
	if (m_size.load() == 0) {
		// cout << "empty: next block not ready" << endl;
		while (m_size.load() <= 0) {
			this_thread::sleep_for(chrono::milliseconds(30));
		}	// wait
	}

	data_mutex.lock();
	current = data.at(0);
	data.erase( data.begin() );
	m_size = data.size();
	data_mutex.unlock();
	return current;
}

void *BaseBuffer::currentBlock() {
	return current;
}

long BaseBuffer::startTime() {
	return current_start;
}

void BaseBuffer::setStart() {
	timeval timeNow;
	gettimeofday(&timeNow, NULL);
	current_start = (timeNow.tv_sec * 1000) + (timeNow.tv_usec / 1000);
}

void BaseBuffer::makeBlocks() {
	int size = 0;
	while (size < maxblocks) {
		void *make = makeBlock();
		data_mutex.lock();
		data.push_back( make );
		m_size = data.size();
		size = m_size.load();
		data_mutex.unlock();
	}

	stop();
}

} /* namespace std */

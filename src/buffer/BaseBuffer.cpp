/*
 * BaseBuffer.cpp
 *
 *  Created on: 9/08/2013
 *      Author: remnanjona
 */

#define maxblocks 100

#include <iostream>
#include "BaseBuffer.h"

namespace std {

BaseBuffer::BaseBuffer(): m_stop(true), m_thread(), data(5) {
	blocksize = 1024*16;
	//m_stop = true;;
}

BaseBuffer::~BaseBuffer() {
	try { stop(); } catch(...) { /*??*/ }
};

void BaseBuffer::stop() {
	cout << "stop" << endl;
	m_stop = true;
	m_thread.join();
}

long BaseBuffer::getBlockLength() {
	return blocksize;
}

void *BaseBuffer::nextBlock() {


	if (data.size() < maxblocks + 1 && m_stop) {
		m_stop = false;
		cout << "start" << endl;
		m_thread = thread(&BaseBuffer::makeBlocks, this);
	}

	cout << data.size() << endl;
	if (data.empty()) return 0;

	void *item = data.at(0);
	data.erase( data.begin() );
	return item;
}

void BaseBuffer::makeBlocks() {
	cout << "making blocks" << endl;
	while (data.size() < maxblocks) {
		data.push_back( makeBlock() );
	}
	stop();
}

} /* namespace std */

/*
 * WavBuffer.cpp
 *
 *  Created on: Mar 27, 2013
 *      Author: remnanjona
 */

#include <stdlib.h>
#include <math.h>
#include "WavBuffer.h"

namespace std {

WavBuffer::WavBuffer(const char *fname) {
	file.open(fname, ios::in | ios::binary);
	if (!file) {
		cout << "file " << fname << " not found" << endl;
	}

	file.seekg (0, ios::beg);
	//file.read ( (char *)array, length*2 );

	ReadRIFF();
	ReadFMT();



	int chunk2Id = 0;
	int chunk2Size = 0;
	file.read ( (char *)&chunk2Id, sizeof(int) );
	file.read ( (char *)&chunk2Size, sizeof(int) );
	cout << "chunk2Size = " << chunk2Size << endl;
	length = chunk2Size;
	array = new short [length];
	file.read ( (char *)array, chunk2Size );

	file.close();
}

void WavBuffer::ReadRIFF() {
	file.read ( (char *)&header, sizeof(RIFF) );
	//cout << "header: "<< header.ChunkID << ", "  << header.ChunkSize << ", " << header.Format << endl;
}

void WavBuffer::ReadFMT() {
	file.read ( (char *)&format, sizeof(FMT) );
	cout << "format: "<< format.channels << ", " << format.sampleRate << ", " <<format.bitsPerSample << endl;
}

long WavBuffer::getLength() {
	return length;
}

short *WavBuffer::getData() {
	return array;
}

int WavBuffer::getFormat() {
	return 0;
}

long WavBuffer::getBlockLength() {
	return length;
}

void *WavBuffer::nextBlock() {
	return array;
}

void *WavBuffer::currentBlock() {
	return array;
}

long WavBuffer::startTime() {
	return 0;
}
void WavBuffer::setStart() {
	// do nothing
}

WavBuffer::~WavBuffer() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

/*
 * WavBuffer.h
 *
 *  Created on: Mar 27, 2013
 *      Author: remnanjona
 */

#ifndef WAVBUFFER_H_
#define WAVBUFFER_H_

#include <iostream>
#include <fstream>
#include "../playback/source.h"

namespace std {

struct RIFF {
	int ChunkID;
	int ChunkSize;
	int Format;
};

struct FMT {
	int ID;
	int size;
	short format;
	short channels;
	int sampleRate;
	int byteRate;
	short blockAlign;
	short bitsPerSample;
};

class WavBuffer: public source {
protected:
	RIFF header;
	FMT format;
	long length;
	short *array;
	ifstream file;
public:
	WavBuffer(const char *);
	void ReadRIFF();
	void ReadFMT();
	virtual long getLength();
	virtual short *getData();

	virtual int getFormat();
	virtual long getBlockLength();
	virtual void *nextBlock();
	virtual void *currentBlock();
	virtual long startTime();
	virtual void setStart();
	virtual ~WavBuffer();
};

} /* namespace std */
#endif /* WAVBUFFER_H_ */

/*
 * wav.h
 *
 *  Created on: 29/10/2014
 *      Author: remnanjona
 */

#ifndef WAV_H_
#define WAV_H_

#include <string>

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

void saveWav(string, short *s, long);
void writeRIFF(ofstream &, RIFF &);
void writeFMT(ofstream &, FMT &);

class wav {
public:
	wav();
	virtual ~wav();
};

} /* namespace std */

#endif /* WAV_H_ */

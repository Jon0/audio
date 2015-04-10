/*
 * wav.cpp
 *
 *  Created on: 29/10/2014
 *      Author: remnanjona
 */

#include "wav.h"

namespace std {

void saveWav(string fname, short *s, long length) {
	ofstream file;
	file.open(fname, ios::binary);

	RIFF r;
	FMT f;
	writeRIFF(file, r);
	writeFMT(file, f);

	//file.read ( (char *)&chunk2Id, sizeof(int) );
	//file.read ( (char *)&chunk2Size, sizeof(int) );
	//file.read ( (char *)s, length );

	file.close();
}

void writeRIFF(ofstream &file, RIFF &r) {
	file.write( (char *)&r, sizeof(RIFF) );
}

void writeFMT(ofstream &file, FMT &f) {
	file.write( (char *)&f, sizeof(FMT) );
}

wav::wav() {
	// TODO Auto-generated constructor stub

}

wav::~wav() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

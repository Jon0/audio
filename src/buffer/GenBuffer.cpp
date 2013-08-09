/*
 * GenBuffer.cpp
 *
 *  Created on: 7/08/2013
 *      Author: remnanjona
 */

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "GenBuffer.h"

namespace std {

GenBuffer::GenBuffer() {
	srand( time( NULL ) );

	int blocklen = 124; //1024*32;
	int blocks = 1024; //128;

	length = blocks*blocklen;
	buffer = new short[length];

	char state[12] = {};

	state[0] = 1;
	state[4] = 1;
	state[7] = 1;
	//state[10] = 1;

	//for (int i = 0; i < 12; ++i) {
	//	state[i] = rand() % 2;
	//}

	int mat[12][12] = {
		{ 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 },
		{ 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1 },
		{ 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1 },
		{ 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1 },
		{ 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1 },
		{ 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1 },
		{ 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
	};

	for (int i = 0; i < 12*12; ++i) {
		mat[i%12][i/12] = rand() % 2;
	}

	float ratio = pow(2, 1.0/12.0);
	float inc[12] = {};
	for (int freq = 0; freq < 12; ++freq) {
		inc[freq] = 100.0 / (440.0 * pow(ratio, freq) ); //2
	}
	float off[12] = {};
	float offa = 0;

	for (int b = 0; b < blocks; ++b) {
		cout << b << "/" << blocks << endl;

		for (int v = 0; v < blocklen; ++v) {

			for (int freq = 0; freq < 12; ++freq) {
				if (state[freq] > 0) {
					buffer[blocklen * b + v] += sin( off[freq] ) * 100.0;
					off[freq] += inc[freq];
					offa += inc[freq];
				}

			}

			//buffer[blocklen * b + v] += sin( offa ) * 1000.0;

		}

		// multiply matrix
		for (int i = 0; i < 12; ++i) {
			int k = 0;
			for (int j = 0; j < 12; ++j) {
				k += mat[j][i] * state[j];
			}
			state[i] = k % 2;
		}
	}



}

int GenBuffer::getFormat() {
	return 0;
}

long GenBuffer::getBlockLength() {
	return 0;
}

void *GenBuffer::nextBlock() {
	return 0;
}

long GenBuffer::getLength() {
	return length;
}

short *GenBuffer::getData() {
	return buffer;
}

GenBuffer::~GenBuffer() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

/*
 * Buffer.cpp
 *
 *  Created on: Mar 11, 2013
 *      Author: remnanjona
 */

#include <iostream>
#include <math.h>
#include "TestBuffer.h"

namespace std {

TestBuffer::TestBuffer() {
	// create 0 matrix
	for (int i = 0; i < mx*mx; ++i) {
		mat[i%mx][i/mx] = 0;
	}

	// set cycle of 5ths bits in matrix
	for (int i = 0; i < mx; ++i) {
		currentf_d[i] = 1.0;
		mat[i][(i+7)%mx] = 1;
		off[i] = 0.0f;
	}

	// set more random bits
	for (int i = 0; i < 16; ++i) {
		mat[rand()%mx][rand()%mx] = 1;
	}


	back = 32;
	state = new char *[back];
	for (int i = 0; i < back; ++i) {
		state[i] = new char [mx];
		state[i][0] = 1;

		//for (int j = 0; j < mx; ++j) {

		//	state[i][j] = rand() % 2;
		//}
	}


	// calculate tuning values for each frequency
	ratio = pow(2, 1.0/12.0);
	inc[mx] = {};
	for (int freq = 0; freq < mx; ++freq) {
		float freqHz = (110.0f * pow(ratio, freq));
		inc[freq] =  2.0f*M_PI / ( 22050.0f / freqHz );
		//cout << ( 22050.0f / freqHz ) << " hz" << endl;

	}
	off[mx] = {};

	time = 0;
}

TestBuffer::~TestBuffer() {
	// TODO Auto-generated destructor stub
}

void *TestBuffer::makeBlock() {
	short *buffer = new short[blocksize]();


	vector<note> nts = tree.sample(time, time + blocksize);
	for (note nt: nts) {
		unsigned int a = max(nt.start, time) - time;
		unsigned int b = min(nt.start + nt.length, time + blocksize ) - time;

		// note completion at point a
		// time = 1000, nstart = 700, length = 1000 ... so a = 0, os = 300
		// time = 0, nstart = 700, length = 1000 ... so a = 700, os = -700
		unsigned int os = time - nt.start;

		for (int v = a; v < b; ++v) {
			unsigned int nfreq = nt.value;
			float p = ((float)(v+os) / nt.length);
			float volume1 = p * (1.0f - p) * 4;
			buffer[v] += sin( off[nfreq] ) * 300.0 * volume1;
			off[nfreq] += inc[nfreq];
		}
	}
	time += blocksize;


//	unsigned int next = s1.next();
//	unsigned int freq = 6 + ((7 * next) % 12);
//	unsigned int nextx = s1.next();
//	unsigned int freqx = freq + nextx % 24;
//	float length = blocksize;
//	float g = 0.0f;
//	for (int v = 0; v < blocksize / 2; ++v) {
//		float p = ((float)v / blocksize);
//		float volume1 = p * (1.0f - p) * 4;
//		buffer[v] += sin( off[freq] ) * 1000.0 * volume1;
//		off[freq] += inc[freq];
//
//		float p2 = ((float)v / (blocksize / 2) );
//		float volume2 = p2 * (1.0f - p2) * 4;
//		buffer[v] += sin( off[freqx] ) * 1000.0 * volume2;
//		off[freqx] += inc[freqx];
//	}
//	nextx = s1.next();
//	freqx = freq + nextx % 24;
//	for (int v = blocksize / 2; v < blocksize; ++v) {
//		float p = ((float)v / blocksize);
//		float volume1 = p * (1.0f - p) * 4;
//		buffer[v] += sin( off[freq] ) * 1000.0 * volume1;
//		off[freq] += inc[freq];
//
//		float p2 = ((float)(v - blocksize / 2) / (blocksize / 2) );
//		float volume2 = p2 * (1.0f - p2) * 4;
//		buffer[v] += sin( off[freqx] ) * 1000.0 * volume2;
//		off[freqx] += inc[freqx];
//	}

	return (void *) buffer;
}

void TestBuffer::mult() {
	// produce next state
	delete state[0];
	for (int i = 0; i < back-1; ++i) {
		state[i] = state[i + 1];
	}
	state[back-1] = new char [mx];

	// multiply matrix
	for (int i = 0; i < mx; ++i) {
		int k = 0;
		for (int j = 0; j < mx; ++j) {
			k += mat[j][i] * state[back-2][j];
		}
		state[back-1][i] = k % 2;
	}

	//cout << "multiplication done" << endl;
}

int TestBuffer::getFormat() {
	return 0;
}

} /* namespace std */


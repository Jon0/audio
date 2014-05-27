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
		inc[freq] =  ( 2.0*M_PI / 44100.0 ) * ( 110.0 * pow(ratio, freq) ); //50.0
	}
	off[mx] = {};

	f1 = 0;
	f2 = 1;

	fx1 = 0;
	fx2 = 1;
}

TestBuffer::~TestBuffer() {
	// TODO Auto-generated destructor stub
}

void *TestBuffer::makeBlock() {
//	mult();
//	char *currenti = new char[mx];
//	for (int i= 0; i < mx; ++i) {
//		//currentf[i] /= 8.0;
//		currentf[i] += (state[back - 1][i] + state[back - 2][i]
//				+ state[back - 3][i] + state[back - 5][i] + state[back - 7][i]
//				+ state[back - 11][i] + state[back - 13][i] + state[back - 17][i] + state[back - 19][i]);
//		currenti[i] = ((int) currentf[i]) % 2;
//
//		currentf_d[i] = 256 + (rand() % 256); //((float)(16384 + (rand() % 32) - 16))/ 2048.0;
//	}
	//state[back - 1] = currenti;

	short *buffer = new short[blocksize]();


	int next = f1 + f2;
	f1 = f2;
	f2 = next;

	int nextx = fx1 + fx2;
	fx1 = f2;
	fx2 = next;


	int freq = 6 + next % 12;
	int freqx = freq + nextx % 24;


	for (int v = 0; v < blocksize / 2; ++v) {
		buffer[v] += sin( off[freq] ) * 1000.0;
		off[freq] += inc[freq];

		buffer[v] += sin( off[freqx] ) * 1000.0;
		off[freqx] += inc[freqx];
	}

	nextx = fx1 + fx2;
	fx1 = f2;
	fx2 = next;
	freqx = freq + nextx % 24;

	for (int v = blocksize / 2; v < blocksize; ++v) {
		buffer[v] += sin( off[freq] ) * 1000.0;
		off[freq] += inc[freq];

		buffer[v] += sin( off[freqx] ) * 1000.0;
		off[freqx] += inc[freqx];
	}

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


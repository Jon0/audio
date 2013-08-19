/*
 * Random.cpp
 *
 *  Created on: 19/08/2013
 *      Author: remnanjona
 */

#include <iostream>
#include <math.h>
#include "Random.h"

namespace std {

Random::Random() {
	for (int i = 0; i < mx*mx; ++i) {
		mat[i%mx][i/mx] = 0; //rand() % 2;
	}

	for (int i = 0; i < mx; ++i) {
		currentf_d[i] = 1.0;
		mat[i][(i+7)%mx] = 1;
	}

	for (int i = 0; i < 16; ++i) {
		mat[rand()%mx][rand()%mx] = 1;	// random bits
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


	ratio = pow(2, 1.0/12.0);
	inc[mx] = {};
	for (int freq = 0; freq < mx; ++freq) {
		inc[freq] =  ( 2.0*M_PI / 44100.0 ) * ( 110.0 * pow(ratio, freq) ); //50.0
	}
	off[mx] = {};
}

Random::~Random() {
	// TODO Auto-generated destructor stub
}

void *Random::makeBlock() {
	mult();
	char *currenti = new char[mx];
	for (int i= 0; i < mx; ++i) {
		currentf[i] /= 8.0;
		currentf[i] += (state[back - 1][i] + state[back - 2][i]
				+ state[back - 3][i] + state[back - 5][i] + state[back - 7][i]
				+ state[back - 11][i] + state[back - 13][i] + state[back - 17][i] + state[back - 19][i]);
		currenti[i] = ((int) currentf[i]) % 2;

		currentf_d[i] = 256 + (rand() % 256); //((float)(16384 + (rand() % 32) - 16))/ 2048.0;
	}
	//state[back - 1] = currenti;

	short *buffer = new short[blocksize]();
	for (int v = 0; v < blocksize; ++v) {

		for (int freq = 0; freq < mx; ++freq) {
			if (currenti[freq] > 0) {


				//currentf_d[freq] *= ((float)(16384 + (rand() % 32) - 16))/ 16384.0;
				//if (currentf[freq] > 4.0) currentf_d[freq] *= 0.98;
				//else if (currentf[freq] < 0.1) currentf_d[freq] *= 1.02;
				currentf[freq] +=  ((float)0.5 + (rand() % 32) - 16) / currentf_d[freq]; //currentf_d[freq] - 1.0;

				buffer[v] += sin( off[freq] ) * 100.0 * currentf[freq];
				off[freq] += inc[freq];

			}

		}
	}

	return (void *) buffer;
}

void Random::mult() {
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

int Random::getFormat() {
	return 0;
}

} /* namespace std */

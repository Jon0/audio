/*
 * fft.cpp
 *
 *  Created on: 3/05/2013
 *      Author: remnanjona
 */

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "fft.h"

namespace std {

fft::fft(source *b) {
	int length = 1024;
	double *dat = new double[1024];
	for (int i = 0; i < length; ++i) {
		dat[i] = sin(i/100.0);
	}

	complex<double> *out = DFT_naive_1(dat, length);

	for (int i = 0; i < length; ++i) {
		cout << i << "\t" << out[i] << endl;
	}

}

complex<double> *fft::DFT_naive_1(double *in, int N) {
	complex<double> *X = new complex<double>[N];
	complex<double> *Nth_root = new complex<double>[N];

	for (int k = 0; k < N; k++) {
		float angle = -2 * M_PI * k / N;
		Nth_root[k] = complex<double>(cos(angle), sin(angle));
	}

	for (int k = 0; k < N; k++) {
		X[k] = 0.0;
		for (int n = 0; n < N; n++) {
			X[k] += in[n] * Nth_root[(n * k) % N];
		}
	}
	delete Nth_root;
	return X;
}

complex<double> *fft::DFT_naive_2(complex<double> *in, int N) {

	complex<double> *X = new complex<double>[N];
    complex<double> *Nth_root = new complex<double>[N];

    for(int k = 0; k < N; k++) {
    	float angle = -2 * M_PI * k/N;
    	Nth_root[k]= complex<double>( cos(angle), sin(angle) );
    }


    for(int k = 0; k<N; k++) {
        X[k].real(0.0);
        X[k].imag(0.0);
        for(int n=0; n<N; n++) {
            X[k] = X[k] + in[n] * Nth_root[(n*k) % N];
        }
    }
    delete Nth_root;
    return X;
}



fft::~fft() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

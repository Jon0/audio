/*
 * fft.h
 *
 *  Created on: 3/05/2013
 *      Author: remnanjona
 */

#ifndef FFT_H_
#define FFT_H_

#include <complex>
#include "../buffer.h"

namespace std {

class fft {
public:
	fft(buffer *);
	complex<double> *DFT_naive_1(double *, int);
	complex<double> *DFT_naive_2(complex<double> *, int);
	virtual ~fft();
};

} /* namespace std */
#endif /* FFT_H_ */

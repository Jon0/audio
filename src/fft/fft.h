#ifndef FFT_H_
#define FFT_H_

#include <complex>
#include "../device/Source.h"

namespace std {

class fft {
public:
	fft(device::Source *);
	complex<double> *DFT_naive_1(double *, int);
	complex<double> *DFT_naive_2(complex<double> *, int);
	virtual ~fft();
};

} /* namespace std */
#endif /* FFT_H_ */

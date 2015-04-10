#include <cmath>
#include <stdlib.h>

#include "Note.h"

namespace score {

Note::Note(double f)
	:
	frequency(f),
	frequency_inv(10000.0 / f) {
	for (int i = 1; i < 60; ++i) {
		v1.push_back((rand() % 10000) / 10000.0);
		v2.push_back((rand() % 10000) / 10000.0);
	}


}

short Note::get(long t) const {
	short r = 0;
	for (int i = 1; i < 60; ++i) {
		double inv = 1.0 / (double) i;
		double k = (t % 40000) / 10000.0;
		if (k > 2.0) k = 2.0 - (k - 2.0);
		r += sin(t / (inv * frequency_inv)) * (inv * 500.0 * (v1[i] * k + v2[i] * (1 - k)));
		r += cos(t / (inv * frequency_inv)) * (inv * 500.0 * (v1[i] * k + v2[i] * (1 - k)));
	}
	return r;
}	

} // namespace score
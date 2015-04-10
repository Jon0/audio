/*
 * Scale.cpp
 *
 *  Created on: 28/10/2014
 *      Author: remnanjona
 */

#include <math.h>

#include "Scale.h"

namespace std {

Scale::Scale() {
	// calculate tuning values for each frequency
	ratio = pow(2, 1.0/12.0);
	inc[mx] = {};
	for (int freq = 0; freq < mx; ++freq) {
		float freqHz = (110.0f * pow(ratio, freq));
		inc[freq] =  2.0f*M_PI / ( 22050.0f / freqHz );
		//cout << ( 22050.0f / freqHz ) << " hz" << endl;

	}
	off[mx] = {};

	n.push_back(24);
	n.push_back(28);
	n.push_back(31);
	n.push_back(36);
	n.push_back(40);

}

Scale::~Scale() {
	// TODO Auto-generated destructor stub
}

short Scale::get(long t) {
	short out = 0;

	// add playing frequencies
	for (int nfreq: n) {
		out += sin( off[nfreq] ) * 100.0;
		off[nfreq] += inc[nfreq];
	}
	return out;
}

} /* namespace std */

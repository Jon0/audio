/*
 * Process.cpp
 *
 *  Created on: Mar 27, 2013
 *      Author: remnanjona
 */

#include <stdio.h>
#include <iostream>
#include "math.h"
#include "Process.h"

namespace std {

Process::Process(device::Source *b) {
	buf = b;

	// sublength, i, and j

	float *pos = new float [2];
	for (int sub = 1; sub < buf->available(); ++sub) {
		printf("complete: %d/%ld\n", sub, buf->available());

		// for every possible start point i that allows given sub length of selection
		for (int i = 0; i < buf->available() - sub; ++i) {

			Vector *x = read(i, sub);
			cout << "x[" << i << "] = ";
			x->print();
			cout << endl;

			for (int j = i + 1; j < buf->available() - sub; ++j) {
				int difference = j - i;

				// make a vector from position/length
				pos[0] = difference;
				pos[1] = sub-1;
				Vector *org = new Vector(2, pos);

				// make vector from content
				Vector *y = x->cross( read(j, sub) );
				cout << "\ty[" << j << "] = ";
				y->print();

				cout << " should match ";
				org->print();
				cout << endl;
				//y->cross(org);

			}
			//printf("complete: %d/%d\n", i, length-sub);
		}
	}
}

Vector *Process::read(int pos, int length) {
	short *data = (short *)buf->currentBlock();
	float *items= new float [2];
	for (int i = 0; i < length; ++i) {
		items[0] += (data[pos+i] * cos((float)i/length));
		items[1] += (data[pos+i] * sin((float)i/length));
	}
	return new Vector(2, items);
}

Process::~Process() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

/*
 * Buffer.cpp
 *
 *  Created on: Mar 11, 2013
 *      Author: remnanjona
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "TestBuffer.h"

namespace std {

TestBuffer::TestBuffer() {
	time = 0;
}

TestBuffer::~TestBuffer() {

}

void *TestBuffer::makeBlock() {
	short *k = new short[blocksize];
	for (int i = 0; i < blocksize; ++i) {
		k[i] = sin(time) * 1000;
		time += 0.08;
	}

	return (void *) k;
}

int TestBuffer::getFormat() {
	return 0;
}

long TestBuffer::getLength() {
	return 0;
}
short *TestBuffer::getData() {
	return 0;
}

} /* namespace std */

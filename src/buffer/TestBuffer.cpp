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
	length = 0;
	array = 0;
}

TestBuffer::TestBuffer(int l) {
	length = l;
	array = new short [length];

	/* ?? */
	for (int i = 0; i < length; ++i) {
		array[i] = rand() % 2048;
	}
}

void TestBuffer::fillNext(int l, int) {
	if (l <= 0) {
		array[l] = rand() % 2048;
		return;
	}
	fillNext(l-1, 0);
}


long TestBuffer::getLength() {
	return length;
}

short *TestBuffer::getData() {
	return array;
}

TestBuffer::~TestBuffer() {
	if (array) delete array;
}

} /* namespace std */

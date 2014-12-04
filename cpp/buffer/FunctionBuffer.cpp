/*
 * GenBuffer.cpp
 *
 *  Created on: 7/08/2013
 *      Author: remnanjona
 */

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "FunctionBuffer.h"

namespace std {

FunctionBuffer::FunctionBuffer(function<short(long)> f): fn(f), t(0) {}

FunctionBuffer::~FunctionBuffer() {}

void *FunctionBuffer::makeBlock() {
	short *buffer = new short[blocksize];
	for (int i = 0; i < blocksize; ++i) buffer[i] = fn(t++);
	return (void *) buffer;
}

} /* namespace std */

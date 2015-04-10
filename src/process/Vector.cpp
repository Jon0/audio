/*
 * Vector.cpp
 *
 *  Created on: 10/03/2013
 *      Author: asdf
 */

#include <stdlib.h>
#include <iostream>
#include "Vector.h"

namespace std {

Vector::Vector(uint i, float *f) {
	elements = i;
	//data = new float [elements];
	//for (int i = 0; i < elements; ++i) data[i] = f[i];
	data = f;
}

Vector *Vector::cross(Vector *other) {
	// check lengths are equal
	if (elements != other->elements) return NULL;

	float *result = new float [elements];
	for (uint i = 0; i < elements; ++i) {
		int k = (i+1)%elements;
		result[i] = data[i]*other->data[k]-data[k]*other->data[i];
	}
	return new Vector(elements, result);
}

void Vector::print() {
	cout << "[";
	for (int i = 0; i < elements-1; ++i) {
		cout << data[i] << ", ";
	}
	cout << data[elements-1] << "]";
}

Vector::~Vector() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */

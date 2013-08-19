/*
 * Matrix.cpp
 *
 *  Created on: 19/08/2013
 *      Author: remnanjona
 */

#include <stdlib.h>
#include "Matrix.h"

Matrix::Matrix(int width, int height) {
	mat = new int [width*height];

	for (int i = 0; i < width*height; ++i) {
		mat[i] = rand() % 2;
	}
	w = width;
	h = height;
}

int Matrix::getWidth() {
	return w;
}

int Matrix::getHeight() {
	return h;
}

int Matrix::getElem(int i, int j) {
	return j*w+i;
}

float *Matrix::VecMultiply(float *vec, int length) {
	float *result = new float [length];
	for (int j = 0; j < h; ++j) {
		int k = 0;
		for (int i = 0; i < length; ++i) {
			k += getElem(i, j) * vec[i];
		}
		result[j] = k % 2;
	}
	return result;
}


Matrix::~Matrix() {
	// TODO Auto-generated destructor stub
}


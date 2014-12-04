/*
 * Matrix.h
 *
 *  Created on: 19/08/2013
 *      Author: remnanjona
 */

#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix {
	int w, h, *mat;

public:
	Matrix(int, int);
	int getWidth();
	int getHeight();
	int getElem(int, int);
	float *VecMultiply(float *vec, int length);
	virtual ~Matrix();
};

#endif /* MATRIX_H_ */

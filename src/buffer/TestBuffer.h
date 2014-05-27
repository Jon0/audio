/*
 * Buffer.h
 *
 *  Created on: Mar 11, 2013
 *      Author: remnanjona
 */

#ifndef TESTBUFFER_H_
#define TESTBUFFER_H_

#define mx 72

#include "BaseBuffer.h"

namespace std {

class TestBuffer: public BaseBuffer {
public:
	TestBuffer();
	~TestBuffer();

	virtual int getFormat();

protected:
	char **state;
	int back, mat[mx][mx];
	float ratio, off[mx], inc[mx];
	float currentf[mx];
	float currentf_d[mx];

	int f1, f2, fx1, fx2;

	void mult();
	virtual void *makeBlock();


};

} /* namespace std */
#endif /* BUFFER_H_ */

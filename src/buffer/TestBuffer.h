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
#include "../math/Series.h"
#include "../math/TimeTree.h"

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

	unsigned int time;
	Series s1;
	TimeTree tree;

	void mult();
	virtual void *makeBlock();


};

} /* namespace std */
#endif /* BUFFER_H_ */

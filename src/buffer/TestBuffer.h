/*
 * Buffer.h
 *
 *  Created on: Mar 11, 2013
 *      Author: remnanjona
 */

#ifndef TESTBUFFER_H_
#define TESTBUFFER_H_

#include "../buffer.h"

namespace std {

class TestBuffer: public buffer {
protected:
	long length;
	short *array;
public:
	TestBuffer();
	TestBuffer(int);
	void fillNext(int, int);
	virtual long getLength();
	virtual short *getData();
	virtual ~TestBuffer();
};

} /* namespace std */
#endif /* BUFFER_H_ */

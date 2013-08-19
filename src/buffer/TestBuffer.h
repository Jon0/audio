/*
 * Buffer.h
 *
 *  Created on: Mar 11, 2013
 *      Author: remnanjona
 */

#ifndef TESTBUFFER_H_
#define TESTBUFFER_H_

#include "BaseBuffer.h"

namespace std {

class TestBuffer: public BaseBuffer {
public:
	TestBuffer();
	~TestBuffer();

	virtual int getFormat();

protected:
	float time, f;
	virtual void *makeBlock();


};

} /* namespace std */
#endif /* BUFFER_H_ */

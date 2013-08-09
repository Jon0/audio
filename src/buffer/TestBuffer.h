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
	virtual long getLength();
	virtual short *getData();

protected:
	float time;
	virtual void *makeBlock();


};

} /* namespace std */
#endif /* BUFFER_H_ */

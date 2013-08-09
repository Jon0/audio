/*
 * GenBuffer.h
 *
 *  Created on: 7/08/2013
 *      Author: remnanjona
 */

#ifndef GENBUFFER_H_
#define GENBUFFER_H_

#include "../source.h"

namespace std {

class GenBuffer: public source  {
protected:
	long length;
	short *buffer;
public:
	GenBuffer();
	virtual int getFormat();
	virtual long getLength();
	virtual long getBlockLength();
	virtual short *getData();
	virtual void *nextBlock();
	virtual ~GenBuffer();
};

} /* namespace std */
#endif /* GENBUFFER_H_ */

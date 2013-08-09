/*
 * GenBuffer.h
 *
 *  Created on: 7/08/2013
 *      Author: remnanjona
 */

#ifndef GENBUFFER_H_
#define GENBUFFER_H_

#include "../buffer.h"

namespace std {

class GenBuffer: public buffer  {
protected:
	long length;
	short *buffer;
public:
	GenBuffer();
	virtual long getLength();
	virtual short *getData();
	virtual ~GenBuffer();
};

} /* namespace std */
#endif /* GENBUFFER_H_ */

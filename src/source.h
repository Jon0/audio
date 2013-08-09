/*
 * buffer.h
 *
 *  Created on: 2/05/2013
 *      Author: asdf
 */

#ifndef BUFFERG_H_
#define BUFFERG_H_
namespace std {

class source {
public:
	virtual int getFormat() = 0;
	virtual long getLength() = 0;
	virtual long getBlockLength() = 0;
	virtual short *getData() = 0;
	virtual void *nextBlock() = 0;
	virtual ~source() {};
};

} /* namespace std */
#endif /* BUFFER_H_ */

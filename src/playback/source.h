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
	virtual ~source() {};
	virtual int getFormat() = 0;
	virtual long getBlockLength() = 0;
	virtual void *nextBlock() = 0;
	virtual void *currentBlock() = 0;
	virtual long startTime() = 0;
	virtual void setStart() = 0;
};

} /* namespace std */
#endif /* BUFFER_H_ */

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

	// available gives how much can be
	// read before calling next again
	virtual long available() = 0;
	virtual void *next() = 0;


	// unused?
	virtual void *currentBlock() = 0;
	virtual long startTime() = 0;

	/**
	 * called when playback begins
	 */
	virtual void setStart() = 0;
};

} /* namespace std */
#endif /* BUFFER_H_ */

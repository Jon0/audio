/*
 * buffer.h
 *
 *  Created on: 2/05/2013
 *      Author: asdf
 */

#ifndef BUFFERG_H_
#define BUFFERG_H_
namespace std {

class buffer {
public:
	virtual long getLength() = 0;
	virtual short *getData() = 0;
	virtual ~buffer() {}
};

} /* namespace std */
#endif /* BUFFER_H_ */

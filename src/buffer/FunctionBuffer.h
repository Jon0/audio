/*
 * GenBuffer.h
 *
 *  Created on: 7/08/2013
 *      Author: remnanjona
 */

#ifndef FUNCTIONBUFFER_H_
#define FUNCTIONBUFFER_H_

#include "BaseBuffer.h"

namespace std {

class FunctionBuffer: public BaseBuffer  {
public:
	FunctionBuffer(function<short(long)>);
	virtual ~FunctionBuffer();

protected:
    void *makeBlock();

private:
    long t;
    function<int(int)> fn;
};

} /* namespace std */
#endif /* FUNCTIONBUFFER_H_ */

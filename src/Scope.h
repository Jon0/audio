/*
 * Scope.h
 *
 *  Created on: 3/05/2013
 *      Author: remnanjona
 */

#ifndef SCOPE_H_
#define SCOPE_H_

#include "Display.h"
#include "buffer.h"

namespace std {

class Scope: public Display {
	buffer *b;
	float view_scale;
	long startTime;
	int width, height;

public:
	Scope(buffer *, int, int);
	virtual void init();
	virtual void start();
	virtual void draw();
	virtual ~Scope();
};

} /* namespace std */
#endif /* SCOPE_H_ */

/*
 * Scope.h
 *
 *  Created on: 3/05/2013
 *      Author: remnanjona
 */

#ifndef SCOPE_H_
#define SCOPE_H_

#include "Display.h"
#include "../playback/source.h"

namespace std {

class Scope: public Display {
	source *b;
	short *g_values_pre;
	float view_scale, format_hz;
	int width, height;

public:
	Scope(source *, int, int);
	virtual void init();
	virtual void draw();
	virtual ~Scope();
};

} /* namespace std */
#endif /* SCOPE_H_ */

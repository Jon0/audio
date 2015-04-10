#ifndef SCOPE_H_
#define SCOPE_H_

#include "Display.h"
#include "../device/Source.h"

namespace std {

/**
 * visualise audio output using opengl
 */
class Scope: public Display {
	device::Source *b;
	short *g_values_pre;
	float view_scale, format_hz;
	int width, height;

public:
	Scope(device::Source *, int, int);
	virtual void init();
	virtual void draw();
	virtual ~Scope();
};

} /* namespace std */
#endif /* SCOPE_H_ */

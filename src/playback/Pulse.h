/*
 * Pulse.h
 *
 *  Created on: 29/08/2013
 *      Author: remnanjona
 */

#ifndef PULSE_H_
#define PULSE_H_

#include <pulse/simple.h>

namespace std {

class Pulse {
public:
	Pulse(const char *);
	virtual ~Pulse();
protected:
	pa_simple *s;
};

} /* namespace std */
#endif /* PULSE_H_ */

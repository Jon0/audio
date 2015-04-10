/*
 * Process.h
 *
 *  Created on: Mar 27, 2013
 *      Author: remnanjona
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "Vector.h"
#include "../device/Source.h"

namespace std {

class Process {
	device::Source *buf;
public:
	Process(device::Source *b);
	Vector *read(int, int);
	virtual ~Process();
};

} /* namespace std */
#endif /* PROCESS_H_ */

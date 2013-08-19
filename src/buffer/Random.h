/*
 * Random.h
 *
 *  Created on: 19/08/2013
 *      Author: remnanjona
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#define mx 48

#include "BaseBuffer.h"

namespace std {

class Random: public BaseBuffer {
public:
	Random();
	virtual ~Random();
	virtual int getFormat();

protected:
	char **state;
	int back, mat[mx][mx];
	float ratio, off[mx], inc[mx];
	float currentf[mx];
	float currentf_d[mx];

	void mult();
	virtual void *makeBlock();
};

} /* namespace std */
#endif /* RANDOM_H_ */

/*
 * Vector.h
 *
 *  Created on: 10/03/2013
 *      Author: asdf
 */

#ifndef VECTOR_H_
#define VECTOR_H_

namespace std {

class Vector {
	uint elements;
	float *data;
public:
	Vector(uint, float *);
	Vector *cross(Vector *);
	void print();
	virtual ~Vector();
};

} /* namespace std */
#endif /* VECTOR_H_ */

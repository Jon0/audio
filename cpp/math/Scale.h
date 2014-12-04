/*
 * Scale.h
 *
 *  Created on: 28/10/2014
 *      Author: remnanjona
 */

#ifndef SCALE_H_
#define SCALE_H_

#include <vector>

#define mx 72

namespace std {

class Scale {
public:
	Scale();
	virtual ~Scale();

	short get(long t);

private:
	vector<int> n;
	float ratio, off[mx], inc[mx];
};

} /* namespace std */

#endif /* SCALE_H_ */

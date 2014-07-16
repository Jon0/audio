/*
 * Series.h
 *
 *  Created on: 16/07/2014
 *      Author: remnanjona
 */

#ifndef SERIES_H_
#define SERIES_H_

#include <vector>

namespace std {

class Series {
public:
	Series();
	virtual ~Series();

	unsigned int next();

private:
	vector<unsigned int> pre;
	unsigned int n;
};

} /* namespace std */

#endif /* SERIES_H_ */

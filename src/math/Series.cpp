/*
 * Series.cpp
 *
 *  Created on: 16/07/2014
 *      Author: remnanjona
 */

#include <iostream>

#include "Series.h"

namespace std {

Series::Series() {
	for (unsigned int i = 0; i < 13; ++i) {
		pre.push_back(rand());
	}
	n = 0;
}

Series::~Series() {
	// TODO Auto-generated destructor stub
}

unsigned int Series::next() {
	unsigned int result = pre[n];


	unsigned int total = 0;
	for (unsigned int i: pre) total += i;
	pre[n] = total;

	n = (n + 1) % pre.size();

	cout << result << endl;
	return result;
}

} /* namespace std */

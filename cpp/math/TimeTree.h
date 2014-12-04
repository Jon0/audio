/*
 * TimeTree.h
 *
 *  Created on: 16/07/2014
 *      Author: remnanjona
 */

#ifndef TIMETREE_H_
#define TIMETREE_H_

#include <memory>
#include <vector>

#include "Series.h"

namespace std {

struct note {
	unsigned int value, start, length;
};

bool within(unsigned int, unsigned int, unsigned int);

class TimeTreeNode {
public:
	TimeTreeNode(Series &, unsigned int, unsigned int, unsigned int, unsigned int);
	virtual ~TimeTreeNode();

	void divide(Series &, unsigned int);

	vector<note> sample(unsigned int, unsigned int);

private:
	vector<shared_ptr<TimeTreeNode>> nodes;
	note note_v;
	unsigned int depth;
	bool played;
};

class TimeTree {
public:
	TimeTree();
	virtual ~TimeTree();

	vector<note> sample(unsigned int, unsigned int);

private:
	shared_ptr<TimeTreeNode> root;
	Series s;

};

} /* namespace std */

#endif /* TIMETREE_H_ */

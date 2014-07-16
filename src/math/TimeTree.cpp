/*
 * TimeTree.cpp
 *
 *  Created on: 16/07/2014
 *      Author: remnanjona
 */

#include "TimeTree.h"

namespace std {

bool within(unsigned int a, unsigned int s, unsigned int e) {
	return a >= s && s <= e;
}

TimeTreeNode::TimeTreeNode(Series &srs, unsigned int b, unsigned int s, unsigned int l, unsigned int d) {
	note_v.value = b + ((7 * srs.next()) % 48) - 24;
	note_v.start = s;
	note_v.length = l;
	depth = d;
	played = depth > 1 && (depth > srs.next() % 6);

	if (depth < 4) {
		unsigned int r = 1 + (srs.next() % 8);
		divide(srs, r);
	}
	else if (note_v.length >= 256*128) {
		unsigned int r = srs.next();
		for (int i = 2; i < 5; ++i) {
			if (r % i == 0) divide(srs, i - 1);
		}
	}

}

TimeTreeNode::~TimeTreeNode() {}

void TimeTreeNode::divide(Series &srs, unsigned int i) {
	//unsigned int newdepth = depth;
	//if (played) newdepth += 1;


	unsigned int sl = note_v.length / i;
	for (int k = 0; k < i; ++k) {
		nodes.push_back( make_shared<TimeTreeNode>(srs, note_v.value, note_v.start + k*sl, sl, depth+1 ) );
	}
}

vector<note> TimeTreeNode::sample(unsigned int s, unsigned int e) {
	vector<note> n;

	if ( within(note_v.start, s, e)
			|| within(note_v.start + note_v.length, s, e) ) {
		if ( played && note_v.value >= 0 && note_v.value < 72 ) n.push_back( note_v );
		for (shared_ptr<TimeTreeNode> nd: nodes) {
			vector<note> inner = nd->sample(s, e);
			n.insert(n.end(), inner.begin(), inner.end());
		}
	}

	return n;
}

TimeTree::TimeTree() {
	root = make_shared<TimeTreeNode>(s, 48, 0, 256*256*256, 0);
}

TimeTree::~TimeTree() {
	// TODO Auto-generated destructor stub
}

vector<note> TimeTree::sample(unsigned int s, unsigned int e) {
	return root->sample(s, e);
}

} /* namespace std */

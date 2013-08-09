/*
 * BaseBuffer.h
 *
 *  Created on: 9/08/2013
 *      Author: remnanjona
 */

#ifndef BASEBUFFER_H_
#define BASEBUFFER_H_

#include <vector>
#include <atomic>
#include <thread>
#include "../source.h"

namespace std {

class BaseBuffer: public source {

public:
	BaseBuffer();
	virtual ~BaseBuffer();

	BaseBuffer(BaseBuffer const&) = delete;
	BaseBuffer& operator =(BaseBuffer const&) = delete;

	void stop();
	virtual long getBlockLength();
	virtual void *nextBlock();

protected:
	int blocksize;
    atomic<bool> m_stop;
    virtual void *makeBlock() = 0;

private:
    thread m_thread;
	vector<void *> data;
    void makeBlocks();
};

} /* namespace std */
#endif /* BASEBUFFER_H_ */

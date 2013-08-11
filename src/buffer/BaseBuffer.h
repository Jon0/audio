/*
 * BaseBuffer.h
 *
 *  Created on: 9/08/2013
 *      Author: remnanjona
 */

#ifndef BASEBUFFER_H_
#define BASEBUFFER_H_

#include <vector>
#include <mutex>
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
	virtual void *currentBlock();

protected:
	int blocksize;
    atomic<bool> m_stop;
    atomic<int> m_size;
    virtual void *makeBlock() = 0;

private:
    thread m_thread;

    // array of blocks
    mutex data_mutex;
	vector<void *> data;

	void *current; 	// the last block used

    void makeBlocks();
};

} /* namespace std */
#endif /* BASEBUFFER_H_ */

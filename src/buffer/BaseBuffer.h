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
#include "../device/Source.h"

namespace std {

class BaseBuffer: public device::Source {

public:
	BaseBuffer();
	virtual ~BaseBuffer();

	BaseBuffer(BaseBuffer const&) = delete;
	BaseBuffer& operator =(BaseBuffer const&) = delete;

	virtual int getFormat();
	long available();
	void *next();


	void *currentBlock();
	long startTime();
	void setStart();

	void stop();

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

	long current_start;
	void *current; 	// the last block used
    void makeBlocks();
};

} /* namespace std */
#endif /* BASEBUFFER_H_ */

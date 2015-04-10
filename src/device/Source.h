#ifndef SOURCE_H_
#define SOURCE_H_

namespace device {

/**
 * a stream of audio data
 */
class Source {
public:
	virtual ~Source() {};
	virtual int getFormat() = 0;

	// available gives how much can be
	// read before calling next again
	virtual long available() = 0;
	virtual void *next() = 0;


	// unused?
	virtual void *currentBlock() = 0;
	virtual long startTime() = 0;

	/**
	 * called when playback begins
	 */
	virtual void setStart() = 0;
};

} /* namespace device */

#endif

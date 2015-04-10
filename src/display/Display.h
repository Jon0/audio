#ifndef DISPLAY_H_
#define DISPLAY_H_

namespace std {

class Display {
public:
	virtual void init() = 0;
	virtual void draw() = 0;
	virtual ~Display() {}
};

} /* namespace std */
#endif /* DISPLAY_H_ */

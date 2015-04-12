#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include <vector>

namespace score {

class Structure {
public:
	Structure();
	Structure(Structure *);
	~Structure();
	
	std::vector<float> values;
};

} // namespace score

#endif
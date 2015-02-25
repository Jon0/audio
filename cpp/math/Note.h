#ifndef NOTE_H_
#define NOTE_H_

#include <vector>

namespace math {

class Note {
public:
	Note(double f);

	const double frequency;
	const double frequency_inv;

	short get(long t) const;

private:
	std::vector<double> v1, v2;

};

} // namespace math

#endif
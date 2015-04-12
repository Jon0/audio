#include <cmath>

#include "Structure.h"

namespace score {

Structure::Structure() {
	int samples = 64;
	for (int i = 0; i < samples; ++i) {
		values.push_back(sin(static_cast<float>(i) / (static_cast<float>(samples) * 2.0f)));
	}
}

Structure::Structure(Structure *s) {
	int samples = s->values.size() * 8;
	values.push_back(0.63f);
	for (int i = 1; i < samples; ++i) {
		float v = s->values[(static_cast<float>(i) / static_cast<float>(samples)) * s->values.size()];
		float p = values[i - 1];
		float next = p + v;
		values.push_back(next - round(next));
	}
}

Structure::~Structure() {}

} // namespace score
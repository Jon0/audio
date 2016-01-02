#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Grid.h"

namespace math {


Grid::Grid(int size)
	:
	gs(size),
	size(size) {
	on.resize(size);
	inc.resize(size);
	amp.resize(size);

	//std::vector<int> tones = {10, 4, 6, 3, 5, 9, 2, 1, 7, 8, 11, 0};
	std::vector<int> tones = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

	double start_freq = 40.0;
	for (int i = 0; i < size; ++i) {
		int tn = tones[i % tones.size()];
		int to = (i / tones.size());
		int nn = to * 12 + tn;
		double hz = start_freq * std::pow(2, static_cast<double>(nn) / 12.0);
		inc[i] = hz * 2.0 * M_PI / 44100.0;
		amp[i] = 0.0;
	}
}


double Grid::get_sample(long t) {
	int blocksize = 1024 * 8;
	int frame = (t / blocksize);
	int modtime = frame % size;
	int block = frame / size;

	double result = 0.0;
	for (int i = 0; i < size; ++i) {
		amp[i] *= 0.999;

		// a wrapping effect
		int tone_map = (i + modtime) % size;
		int block_map = 73231 + block * 7;

		if (gs.is_on(tone_map, modtime, block_map)) {
			amp[i] += 0.0015;
		}
		if (amp[i] > 1) {
			amp[i] = 1.0;
		}
		double boost = (static_cast<double>(size) - static_cast<double>(i)) / static_cast<double>(size);
		result += boost * std::sin(static_cast<double>(t) * inc[i]) * amp[i];
	}
	return result;
}


GridSeries::GridSeries(int size)
	:
	size(size),
	maxprime(2) {

	int ivalue = 0;
	int halfsize = size / 2;
	int startx = halfsize - 1;
	int endx = halfsize;
	int starty = halfsize - 1;
	int endy = halfsize;

	while (startx >= 0) {

		// left
		for (int i = starty + 1; i <= endy; ++i) {
			set_ind(i, startx, ivalue++);
		}

		// top
		for (int i = startx + 1; i <= endx; ++i) {
			set_ind(endy, i, ivalue++);
		}

		// right
		for (int i = endy - 1; i >= starty; --i) {
			set_ind(i, endx, ivalue++);
		}

		// bottom
		for (int i = endx - 1; i >= startx; --i) {
			set_ind(starty, i, ivalue++);
		}

		startx--;
		starty--;
		endx++;
		endy++;
	}
}


bool GridSeries::is_on(int tone, int modtime, int block) {
	return is_prime(get_ind(tone, modtime) + block);
}


bool GridSeries::is_prime(int i) {
	if (i > maxprime) {
		for (int p = maxprime; p < i; ++p) {
			int rt = std::sqrt(i);
			bool addprime = true;
			for (int t = 2; t <= rt; ++t) {
				if (prime.count(t) > 0 && p % t == 0) {
					addprime = false;
				}
			}
			if (addprime) {
				std::cout << "prime " << p << "\n";
				prime.insert(p);
			}
		}
		maxprime = i;
	}
	return prime.count(i) > 0;
}


int GridSeries::get_ind(int tone, int modtime) {
	return ind.at(tone * size + modtime);
}

void GridSeries::set_ind(int tone, int modtime, int index) {
	ind[tone * size + modtime] = index;
}


}

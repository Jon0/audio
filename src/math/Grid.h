#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace math {


class GridSeries {
public:
	GridSeries(int size);

	bool is_on(int tone, int modtime, int block);
	bool is_prime(int i);

private:
	int get_ind(int tone, int modtime);
	void set_ind(int tone, int modtime, int index);

	const int size;
	int maxprime;
	std::unordered_map<int, int> ind;
	std::unordered_set<int> prime;

};


class Grid {
public:
	Grid(int size);

	double get_sample(long t);

private:
	GridSeries gs;
	const int size;
	std::vector<bool> on;
	std::vector<double> inc;
	std::vector<double> amp;

};


}

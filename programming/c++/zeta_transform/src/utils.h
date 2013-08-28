#ifndef UTILS_H
#define UTILS_H

#include <vector>

namespace utils {
	void fast_zeta_transform_exp_space(int, std::vector<int>*); 
	void pick_n2(int*, int*, int, int, int);
	int count_1bits(int);
	int power_of_minus_one(int);
}

#endif

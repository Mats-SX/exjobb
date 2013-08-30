#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "polynomial.h"

namespace utils {
//	template <typename T>
//	void fast_zeta_transform_exp_space(int, std::vector<T>*); 
	void fast_zeta_transform_exp_space(int, std::vector<Polynomial>*); 
	void fast_zeta_transform_exp_space(int, std::vector<int>*); 
	void pick_n2(int*, int*, int, int, int);
	int count_1bits(int);
	int power_of_minus_one(int);
}

#endif

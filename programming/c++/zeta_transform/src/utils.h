#ifndef UTILS_H
#define UTILS_H

#include "types.h"

namespace utils {
	void fast_zeta_transform_exp_space(int_t, rval_list_t*);
	void fast_zeta_transform_linear_space(int_t, int_t, int_list_t*, rval_list_t*);
	void pick_n2(int_t&, int_t&, const int_t&, const int_t&, const int);
	int_t count_1bits(int);
	int_t count_1bits(long long);
	int_t count_1bits();
	int_t power_of_minus_one(int_t);
}

#endif

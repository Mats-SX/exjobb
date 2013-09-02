#ifndef UTILS_H
#define UTILS_H

#include "types.h"

namespace utils {
<<<<<<< HEAD
	void fast_zeta_transform_exp_space(int_t, rval_list_t*);
	void fast_zeta_transform_linear_space(int_t, int_t, int_list_t*, rval_list_t*);
	void pick_n2(int_t*, int_t*, int_t, int_t, int);
	int_t count_1bits(int);
	int_t count_1bits(long long);
	int_t count_1bits();
	int_t power_of_minus_one(int_t);
=======
//	template <typename T>
//	void fast_zeta_transform_exp_space(int, std::vector<T>*); 
	void fast_up_zeta_transform_exp_space(int, std::vector<Polynomial>*);
	void fast_zeta_transform_exp_space(int, int**, int);
	void fast_zeta_transform_exp_space(int, std::vector<Polynomial>*); 
	void fast_zeta_transform_exp_space(int, std::vector<int>*); 
	void pick_n2(int*, int*, int, int, int);
	int count_1bits(int);
	int power_of_minus_one(int);
>>>>>>> Cleaned up in preparation for the wrapper type implementation.
}

#endif

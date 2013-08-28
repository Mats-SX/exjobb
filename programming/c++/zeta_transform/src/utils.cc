#include <math.h>
#include "utils.h"

using namespace std;

/*
 * This is the 'trivial' Fast Zeta Transform, in exponential time and space.
 * The vector f contains sets in Gray Code, with each element in f corresponding
 * to the function value of the subset whose Gray Code is the index of the element.
 *
 * The function iterates over all subsets of each set and sums the function values, 
 * overwriting the existing vector elements with the sums.
 *
 * This function works as a utility function for the Fast Zeta Transform in Linear Space
 * algorithm.
 */
void utils::fast_zeta_transform_exp_space(int n, vector<int>* f) {

	for (int j = 1; j <= n; ++j) {
		int index = 0;
		int step = pow(2, j-1);
		while (index < f->size()) {
			index += step;
			for (int i = 0; i < step; ++i) {
				(*f)[index] += (*f)[index - step];
				++index;
			}
		}
	}

	return;
}

/*
 * This is a utility function for the choice of how to split the n-sized universe U
 * into two disjoint parts U1 and U2, of sizes n1 and n2 respectively. U is never
 * explicitly defined, as it suffices to work with n.
 */
void utils::pick_n2(int* n1, int* n2, int f_size, int n, int split_decision) {

	switch (split_decision) {
		case -1:
			*n2 = ceil(log2(f_size));
			break;
		case 0:
			*n2 = n / 2;
			break;
		case 1:
			*n2 = 0;
			break;
		case 2:
			*n2 = n - 1;
			break;
	}
	*n1 = n - *n2;
}

// Shameful copy-paste from stackoverflow.com: http://stackoverflow.com/questions/4244274/how-do-i-count-the-number-of-zero-bits-in-an-integer

/*
 * This utility function counts the number of set bits in a 32-bit integer.
 *
 * If the integer is used to represent a set, where 1 means that the bit index value
 * is in the set, this can be interpreted as a function to calculate the size of a set.
 */
int utils::count_1bits(int i) {
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

/*
 * Returns the xth power of -1.
 */
int utils::power_of_minus_one(int x) {
	if ((x & 1) == 0)
		return 1;
	return -1;
}

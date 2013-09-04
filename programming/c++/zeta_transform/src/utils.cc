#include <math.h>
#include "utils.h"
#include "types.h"
#include <iostream>
#include <bitset>

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
void utils::fast_zeta_transform_exp_space(int_t n, rval_list_t* f) {

	for (int_t j = 1; j <= n; ++j) {
		int_t index = 0;
		int_t step = pow(2, j-1);
		while (index < f->size) {
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
 * This function calculates the Fast Zeta Transform in Linear Space for a given problem
 * type.
 *
 * n is split into n1 and n2, where n = n1 + n2 is assumed to hold.
 * family is a pointer to a list of the sets to be used for covering. Each member of the 
 * list is a set represented as a bit vector. A 1-bit in position i means that i is a 
 * member of the set.
 * f represents a function with a one-to-one mapping from each member of family to a 
 * value in an algebraic ring. A 
 */
void utils::fast_zeta_transform_linear_space(
		int_t n1,
		int_t n2,
		int_list_t* family,
		rval_list_t* f,
		int_t k,
		rval_t* ck)
{

	// Variables we only want to calculate once
	int_t two_to_the_n1 = pow(2, n1);		// 2^n1
	int_t two_to_the_n2 = pow(2, n2);		// 2^n2

	int_t u1 = two_to_the_n1 - 1;			// Index of U1 in the range of subsets 2^U
	int_t u2 = pow(2, n1+n2) - two_to_the_n1;	// Index of U2

	// Function g
	rval_list_t g(two_to_the_n2);

	// DEBUG
	//cout << "NOW STARTING THE MAIN LOOP" << endl << endl;

	// Thanks to our constraint on the ordering of F, we can know for sure
	// that the subsets X1 of U1 are the first 2^n1 subsets in F
	// {{ For each subset X1 of U1, do }}
	for (int_t x1 = 0; x1 < two_to_the_n1; ++x1) {
		// x1 is index of X1, but we do not handle X1 explicitly.
		
		//DEBUG
		//cout << "x1: " << x1 << " = " << bitset<7>(x1) << endl;


		// {{ For each Y2 in U2, set g(Y2) <- 0 }}
		for (int_t i = 0; i < two_to_the_n2; ++i) {
			g[i] = 0;	// We just initialize a 0-vector of size 2^n2.
					// I see no need to map these values to specific
					// indices, but instead we make sure we
					// access the proper value when using g.
		}

		// {{ For each Y in F, if YnU1 is a subset of X1, then set g(YnU2) <- g(YnU2) + f(Y) }}
		for (int_t i = 0; i < family->size; ++i) {
			int_t y = (*family)[i];

			//DEBUG
			//cout << "y: " << y << " = " << bitset<7>(y) << endl;

			// {{ if YnU1 is a subset of X1 }}
			// with index math: since u1 is all-ones for elements in U1,
			// y & u1 will be the index of the set YnU1.
			// y & u1 is the index of a subset of X1 iff
			// y & u1 doesn't contain a 1 in any position where X1
			// doesn't contain a 1. 
			// If y & u1 does contain a 1 in a position where X1
			// doesn't, (y & u1) | x1 will be a larger number than x1.
			if (((y & u1) | x1) <= x1) {
				
				// DEBUG
				//cout << "y: " << y << " = " << bitset<7>(y)
				//     << ", u1: " << u1 << " = " << bitset<7>(u1)
				  //   << ", x1: " << x1 << " = " << bitset<7>(x1)
				    // << endl;
				//cout << "y & u1 was subset of x1?" << endl;


				// Since g contains all subsets of U2 in increasing
				// order of index, but indices of subsets of U2 doesn't
				// (generally) come at a distance of 1 from eachother, 
				// they come at a distance of 2^n1 (=1 iff n1=0). Since
				// g doesn't contain "holes", we normalize the distances
				// to 1 like this.
				
				//DEBUG
				//cout << "This is y & u2: " << (y & u2) << endl;
				/*cout << endl;
				cout << "y & u2: " << (y & u2) << " = " << bitset<7>(y & u2) << endl;
				cout << "(y&u2)/2^n1: " << ((y & u2) / two_to_the_n1) << " = "
					<< bitset<7>(((y & u2) / two_to_the_n1)) << endl;
				cout << "f(" << i << ") = " << (*f)[i] << endl;
				*/

				g[(y & u2) / two_to_the_n1] += (*f)[i];
			}
		}
		
		// DEBUG
		/*cout << "\nThese are the values g(Y2) where Y2 are all subsets of U2:" << endl;
		for (int i = 0; i < two_to_the_n2; ++i) {
			cout << "g(" << bitset<7>(i * two_to_the_n1) << "): " << g[i] << endl;
		}*/

		// I don't need another vector, so I re-use g as h.
		// {{ Compute h <- gS using fast zeta transform on 2^U2 }}
		fast_zeta_transform_exp_space(n2, &g);

		// The vector g contains all subsets of U2, in increasing
		// order of index. But the indices of subsets of U2 doesn't come at
		// a distance of 1 from eachother, unlike with U1. They are separarated 
		// by 2^n1 positions.
		// {{ For each subset X2 of U2, output h(X2) as the value fS(X1uX2) }}
	
		
		for (int_t i = 0; i < two_to_the_n2; ++i) {
			int_t x2 = i * two_to_the_n1;
			int_t x = x1 | x2;

			// To print zeta transform fS of f
			
			/*
			cout << "fS(" << bitset<30>(x) 
				<< " = " << x 
				<< "): " << g[i] << endl;
			*/			

			// Calculating k-cover
			int_t size_of_U_minus_X = n1 + n2 - count_1bits(x);
			(*ck) += power_of_minus_one(size_of_U_minus_X) 
				* pow(g[i], k);

			// DEBUG
			/*	
			cout << "x: " << bitset<4>(x) << " = " << x << endl;
			cout << "1s in x: " << utils::count_1bits(x) << endl;
			cout << "|U \\ X| = " << size_of_U_minus_X << endl;
			cout << "-1? " << utils::power_of_minus_one(size_of_U_minus_X) << endl;
			cout << "(fS(x)=" << g[i] << ")^" << k << " = " << pow(g[i], k) << endl;
			cout << *ck << endl;
			*/
		}
	}
	

	return;
}

/*
 * This is a utility function for the choice of how to split the n-sized universe U
 * into two disjoint parts U1 and U2, of sizes n1 and n2 respectively. U is never
 * explicitly defined, as it suffices to work with n.
 */
void utils::pick_n2(int_t* n1, int_t* n2, int_t f_size, int_t n, int split_decision) {

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
int_t utils::count_1bits(int i) {
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

int_t utils::count_1bits(long long i) {
	// hmmm
}

/* For the GMP type... */
int_t utils::count_1bits( /* ... */ ) {
	// hmmm
}

/*
 * Returns the xth power of -1.
 */
int_t utils::power_of_minus_one(int_t x) {
	if ((x & 1) == 0)
		return 1;
	return -1;
}

#include <iostream>
#include <math.h>
#include <vector>
#include "../../zeta_transform/src/utils.h"

using namespace std;

/*
 * The integer set contains a 1 on position i iff vertex i is in the set X.
 * This function returns an integer with a 1 on position i iff vertex i
 * has a neighbour in X.
 */
int neighbours_of(int set) {
	// not sure how we represent the graph
	return 0;
}

/*
 * The integer set contains a 1 on position i iff vertex i is in the set X.
 * This function returns true iff there is no vertex in G \ X with a neighbour in X.
 */
bool independent(int set) {
	// not sure how we represent the graph
	return false;
}

int main(int argc, char** argv) {


	int n;		// Size of V
	int k;		// Number of colors to use.

	// partition the vertices into V1 and V2, of sizes n1 and n2 respectively
	int n1, n2;

	n1 = ceil(n * (log(2) / log(3)));
	n2 = n - n1;
	
	int two_to_the_n1 = pow(2, n1);
	int two_to_the_n2 = pow(2, n2);
	int two_to_the_n = pow(2, n);

	int v1 = two_to_the_n1 - 1 ;
	int v2 = two_to_the_n - two_to_the_n1;

	// Data structures
	// These are supposed to be vectors of polynomials
	// TODO
	vector<int> h(two_to_the_n2);
	vector<int> l(two_to_the_n2);

	// 1.
	// TODO: This is supposed to be a polynomial.
	// How do I represent it?
	int r  = 0;

	// {{ 2. For each subset X1 of V1, do }}
	for (int x1 = 0; x1 <= v1; ++x1) {

		// {{ a) For each subset Z2 of V2, set h(Z2) <- 0 }}
		for (int i = 0; i < two_to_the_n2; ++i) {
			h[i] = 0;
			// We just initialize a 0-vector of size 2^n2.
			// I see no need to map these values to specific
			// indices, but instead we make sure we
			// access the proper value when using g.
		}

		// {{ b) For each subset Y1 of X1, 
		// set h(V2 \ N(Y1)) <- h(V2 \ N(Y1)) + z^(|Y1|) if Y1 independent in G }}
		for (int y1 = 0; y1 < x1; ++y1) {
			// TODO: Fix this loop so it executes in time O*(2^|X1|) instead of ...?

			if ((y1 | x1) <= x1) { // <=> Y1 is subset of X1
				// if Y1 is independent in G
				if (independent(y1)) {
					// This is _polynomial_ addition.
					// How do I represent polynomials again?
					h[v2 & (~ neighbours_of(y1))] += utils::count_1bits(y1);
				}
			}
		}
		

		// {{ c) For each subset Y2 of V2,
		// set l(Y2) <- z^(|Y2|) if Y2 independent in G }}
		for (int i = 0; i < two_to_the_n2; ++i) {
			int y2 = i * two_to_the_n1;
			if (independent(y2)) {
				// l[i] = z^(|Y2|)
				l[i] = utils::count_1bits(y2);
			} else {
				l[i] = 0;
			}
		}

		// {{ d) Set g <- (hS')*l }}
		// TODO
		vector<int> g(two_to_the_n2);
		utils::fast_up_zeta_transform_exp_space(&h, &g);
		for (int i = 0; i < two_to_the_n2; ++i) {
			// polynomial multiplication!
			g[i] = g[i] * l[i];
		}

		// {{ e) Set j <- gS }}
		// TODO
		vector<int> j(two_to_the_n2);
		utils::fast_zeta_transform_exp_space(&g, &l);

		// {{ For each subset X2 of V2,
		// set r <- r + (-1)^(n-|X1|-|X2|) * j(X2)^k }}
		for (int i = 0; i < two_to_the_n2; ++i) {
			int x2 = i * two_to_the_n1;
			int exponent = n - utils::count_1bits(x1) - utils::count_1bits(x2);
			// TODO Polynomial addition and multiplication
			r += utils::power_of_minus_one(exponent) * pow(j[i], k);
		}

	}

	// { 3. Return the coefficient of z^n in r }}
	// TODO: Again, polynomial representation!
	
	
	return 0;
}

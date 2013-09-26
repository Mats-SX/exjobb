#include <iostream>
#include <math.h>
#include <vector>
#include "types.h"
#include "utils.h"
#include <gmp.h>
#include <cstdlib>
#include <fstream>
#include <bitset>

/*
 * The integer set contains a 1 on position i iff vertex i is in the set X.
 * This function returns an integer with a 1 on position i iff vertex i
 * has a neighbour in X.
 */
int_t neighbours_of(int_t set, bool* matrix, int_t n) {
//	std::cout << "set: " << set << "=" << std::bitset<3>(set) << std::endl;
	if (!set)	// empty set, has no neighbours
		return 0;
	int_t vertex = 0;
	std::vector<int_t> vertices;
	while (set) {		// as long as set != emptyset
		if (set % 2)	// set has 1 in last pos, vertex is in set
			vertices.push_back(vertex);
		set = set >> 1;	// set next element as last
		++vertex;	// proceed to next vertex
	}
	int_t neighbours = 0;
	for (int_t i = 0; i < vertices.size(); ++i) {
		for (int_t j = 0; j < n; ++j) {
			if (matrix[n * vertices[i] + j]) {
				neighbours |= 1 << j;	// 1 in pos j
			}
		}
	}
//	std::cout << "neighbours: " << neighbours << "=" << std::bitset<3>(neighbours) << std::endl;
	return neighbours;
}

/*
 * This function returns a pointer to the first element of a smallest-first ordered
 * list of vertex numbers present in the set set. 
 */
void vertices_in(int_t set, int_t* list) {
	int_t vertex = 0;
	int_t i = 0;
	while (set) {		// as long as set != emptyset
		if (set % 2) {	// set has 1 in last pos, vertex is in set
			list[i] = vertex;
			++i;
		}
		set = set >> 1;	// set next element as last
		++vertex;	// proceed to next vertex
	}
//	return list;
}

/*
 * The integer set contains a 1 on position i iff vertex i is in the set X.
 * This function returns true iff there is no vertex in G \ X with a neighbour in X.
 */
bool independent(int_t set, bool* matrix, int_t n) {
	//DEBUG
//	std::cout << "entering independent()" << std::endl;
//	std::cout << "set: " << set << "=" << std::bitset<3>(set) << std::endl;

	if (!set)	// empty set
		return true;
	int_t vertex = 0;
	std::vector<int_t> vertices;
	while (set) {		// as long as set != emptyset
		if (set % 2)	// set has 1 in last pos, vertex is in set
			vertices.push_back(vertex);

		set = set >> 1;	// set next element as last
		++vertex;	// proceed to next vertex
	}
	for (int_t i = 0; i < vertices.size(); ++i) {
		for (int_t j = i + 1; j < vertices.size(); ++j) {
			if (matrix[n * vertices[i] + vertices[j]]) {
				//DEBUG
//				std::cout << "found connection. not independent" << std::endl;
				return false;
			}
		}
	}
	//DEBUG
//	std::cout << "didnt find connection" << std::endl;
	return true;
}

/*
 * This function could perform better. For an undirected graph,
 * there is no need for a complete adjacency matrix. In fact, we 
 * do not even have self-edges, so less than half of the matrix is
 * needed as output.
 */
void parse(std::ifstream& infile, bool* matrix, int_t n) {
	for (int_t i = 0; i < n; ++i) {
		for (int_t j = 0; j < n; ++j) {
			int v;
			infile >> v;
			matrix[i * n + j] = v != 0;
		}
	}
}

int main(int argc, char** argv) {

	if (argc != 3)
		std::cout << "Usage: <prg> <infile> <k>" << std::endl;

	std::ifstream infile(argv[1]);
	
	int_t n;		// Size of V
	int_t k;		// Number of colors to use.

	infile >> n;
	k = atoi(argv[2]);

	bool* matrix = new bool[n*n];
	parse(infile, matrix, n);

	// partition the vertices into V1 and V2, of sizes n1 and n2 respectively
	int_t n1, n2;

	n1 = ceil(n * (log(2) / log(3)));
	n2 = n - n1;

	std::cout << "n1: " << n1 << ", n2: " << n2 << std::endl;

	int_t two_to_the_n1 = pow(2, n1);
	int_t two_to_the_n2 = pow(2, n2);
	int_t two_to_the_n = pow(2, n);

	int_t v1 = two_to_the_n1 - 1 ;
	int_t v2 = two_to_the_n - two_to_the_n1;

	//DEBUG
//	std::cout << "v1: " << v1 << "=" << std::bitset<3>(v1) << std::endl;
//	std::cout << "v2: " << v2 << "=" << std::bitset<3>(v2) << std::endl;

	// 1.
	rval_t r;
	r.set_degree(n);

	// {{ 2. For each subset X1 of V1, do }}
	for (int_t x1 = 0; x1 <= v1; ++x1) {

		//DEBUG
//		std::cout << "x1: " << x1 << "=" << std::bitset<3>(x1) << std::endl;

		// Data structures
		rval_list_t h(two_to_the_n2);
		rval_list_t l(two_to_the_n2);
		
		// {{ a) For each subset Z2 of V2, set h(Z2) <- 0 }}
		for (int i = 0; i < two_to_the_n2; ++i) {
			h[i].set_degree(n);
			// We just initialize a 0-vector of size 2^n2.
			// I see no need to map these values to specific
			// indices, but instead we make sure we
			// access the proper value when using g.
		}

		// {{ b) For each subset Y1 of X1, 
		// set h(V2 \ N(Y1)) <- h(V2 \ N(Y1)) + z^(|Y1|) if Y1 independent in G }}
		for (int_t y1 = 0; y1 <= x1; ++y1) {
			// TODO: Fix this loop so it executes in time 2^|X1| instead of 2^c
			// where c is the position of the most significant bit of x1, or, in 
			// set terms, the highest-numbered vertex present in X1.


			if ((y1 | x1) <= x1) { // <=> Y1 is subset of X1
				// if Y1 is independent in G
				//DEBUG:
//				std::cout << "this is a subset of x1: " << std::endl;
//				std::cout << "y1: " << y1 << "=" << std::bitset<3>(y1) << std::endl;
				if (independent(y1, matrix, n)) {

					//DEBUG
//					std::cout << "y1 was deemed independent" << std::endl;


					Polynomial p;
					p.set_degree(n);
					int_t size_of_y1 = utils::count_1bits(y1);
					mpz_set_ui(p[size_of_y1], 1);		// p = 1z^(|y1|)

					//DEBUG:
//					int neigh = neighbours_of(y1, matrix, n);
//					std::cout << "neighbours of y1: " << std::bitset<3>(neigh) << std::endl;
//					std::cout << "pol before: (index is " << ((v2 & (~neigh)) / two_to_the_n1);
//					std::cout << h[(v2 & (~neigh)) / two_to_the_n1] << std::endl;
//					std::cout << "p: " << p << std::endl;

					h[(v2 & (~ neighbours_of(y1, matrix, n))) / two_to_the_n1] += p;
					//DEBUG
//					std::cout << "pol after: ";
//					std::cout << h[(v2 & (~neigh)) / two_to_the_n1] << std::endl;
				}
			}
		}
		

		// {{ c) For each subset Y2 of V2,
		// set l(Y2) <- z^(|Y2|) if Y2 independent in G }}
		for (int_t i = 0; i < two_to_the_n2; ++i) {
			int_t y2 = i * two_to_the_n1;

			l[i].set_degree(n);
			
			// DEBUG
//			std::cout << "y2: " << y2 << "=" << std::bitset<3>(y2) << std::endl;
			
			if (independent(y2, matrix, n)) {
				l[i].set_degree(n);
				int_t size_of_y2 = utils::count_1bits(y2);
				mpz_set_ui(l[i][size_of_y2], 1);	// p = 1z^(|y2|)
			}

			//DEBUG
//			std::cout << "l[i]: " << l[i] << std::endl;
		}

		// {{ d) Set h <- (hS')*l }}
		utils::fast_up_zeta_transform_exp_space(n2, &h);

		for (int_t i = 0; i < two_to_the_n2; ++i) {
			h[i] *= l[i];

			//DEBUG
//			std::cout << "h[i]: " << h[i] << std::endl;
		}

		// {{ e) Set h <- gS }}
		utils::fast_zeta_transform_exp_space(n2, &h);

		// {{ For each subset X2 of V2,
		// set r <- r + (-1)^(n-|X1|-|X2|) * j(X2)^k }}
		for (int_t i = 0; i < two_to_the_n2; ++i) {
			// DEBUG
//			std::cout << "i: " << i << std::endl;
//			std::cout << "h[i]: " << h[i] << std::endl;

			int_t x2 = i * two_to_the_n1;
			int exponent = n - utils::count_1bits(x1) - utils::count_1bits(x2);
			int factor = utils::power_of_minus_one(exponent);			
			h[i].raise_to_the(k);
			h[i] *= factor;
			r += h[i];

			//DEBUG
//			std::cout << "r = " <<  r << std::endl;
		}

	}

	// { 3. Return the coefficient of z^n in r }}
	std::cout << "Coefficient of z^n is " << r[n] << std::endl;
	
	return 0;
}

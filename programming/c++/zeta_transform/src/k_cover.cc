#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <bitset>
#include <cstdlib>
#include "utils.h"

using namespace std;

// We are assuming for now that the family F of subsets of U to be considered
// is ordered in Gray code order. That is, for each set X = {X1, X2, ..., Xk} in F,
// there is an index i = sum(2^(Xj - 1)) for j = 1, 2, ..., k, and the order
// of the sets X in F is in increasing order of their indices.
//
// family is a vector where the indices of sets in F are stored.
// f is a vector where the values of the function f in the algorithm
// are stored, each corresponding to a subset on same position in F.
void k_cover_linear_space(
		int n1,
		int n2,	
		vector<int>* family, 
		vector<int>* f, 
		int k, 
		int* ck, 
		int split_decision = -1)
{

	// Variables we only want to calculate once
	int two_to_the_n1 = pow(2, n1);		// 2^n1
	int two_to_the_n2 = pow(2, n2);		// 2^n2

	int u1 = two_to_the_n1 - 1;		// Index of U1 in the range of subsets 2^U
	int u2 = pow(2, n1+n2) - two_to_the_n1;	// Index of U2

	// Function g
	vector<int> g(two_to_the_n2);

	// DEBUG
	//cout << "NOW STARTING THE MAIN LOOP" << endl << endl;

	// Thanks to our constraint on the ordering of F, we can know for sure
	// that the subsets X1 of U1 are the first 2^n1 subsets in F
	// {{ For each subset X1 of U1, do }}
	for (int x1 = 0; x1 < two_to_the_n1; ++x1) {
		// x1 is index of X1, but we do not handle X1 explicitly.
		
		//DEBUG
		//cout << "x1: " << x1 << " = " << bitset<7>(x1) << endl;


		// {{ For each Y2 in U2, set g(Y2) <- 0 }}
		for (int i = 0; i < two_to_the_n2; ++i) {
			g[i] = 0;	// We just initialize a 0-vector of size 2^n2.
					// I see no need to map these values to specific
					// indices, but instead we make sure we
					// access the proper value when using g.
		}

		// {{ For each Y in F, if YnU1 is a subset of X1, then set g(YnU2) <- g(YnU2) + f(Y) }}
		for (int i = 0; i < family->size(); ++i) {
			int y = (*family)[i];

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

		// For testing purposes, I safe-copy g here. 
		// Should be removed when we go live.
//		vector<int> safe_copy(g);

		// I don't need another vector, so I re-use g as h.
		// {{ Compute h <- gS using fast zeta transform on 2^U2 }}
		utils::fast_zeta_transform_exp_space(n2, &g);

		// The vector g contains all subsets of U2, in increasing
		// order of index. But the indices of subsets of U2 doesn't come at
		// a distance of 1 from eachother, unlike with U1. They are separarated 
		// by 2^n1 positions.
		// {{ For each subset X2 of U2, output h(X2) as the value fS(X1uX2) }}
	
		
		for (int i = 0; i < two_to_the_n2; ++i) {
			int x2 = i * two_to_the_n1;
			int x = x1 | x2;

			// To print zeta transform fS of f
			/*
			cout << "fS(" << bitset<30>(x) 
				<< " = " << x 
				<< "): " << g[i] << endl;
			*/			

			// Calculating k-cover
			int size_of_U_minus_X = n1 + n2 - utils::count_1bits(x);
			(*ck) += utils::power_of_minus_one(size_of_U_minus_X) 
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



int main(int argc, char** argv) {

	/* Communication with user */

	cout 	<< "Welcome to the Fast Zeta Transform in Linear Space-based algorithm "
		<< "to count the number of k-covers of a Set Cover problem instance." 
		<< endl;
	cout 	<< "This program is constrained to only handling n < 31 and function "
		<< "values f < 2^31. Larger values may cause the program to crash." 
		<< endl << endl;

	int split_decision = -1;
	if (argc == 3) {
		cout	<< "Using default split." 
			<< endl;
	} else if (argc != 4) {
		cout 	<< "Usage: k_cover <infile> <k> <split_decision>."
			<< endl;
		cout	<< "<split_decision> is an integer 0, 1 or 2. "
			<< "Any other value (or none provided) falls to default."
			<< endl
			<< "0 means n1 = n2 = n/2."	<< endl
			<< "1 means n1 = n, n2 = 0."	<< endl
			<< "2 means n1 = 1, n2 = n-1."	<< endl
			<< "Default means n2 = ceil(log2(|F|)), n1 = n-n2."
			<< endl
			<< "Now exiting."
			<< endl;
		return 0;
	} else {
		split_decision = atoi(argv[3]);
	}

	/* Read parameters */

	ifstream infile(argv[1]);		// Streaming from provided file
	int n, m, k;
	infile >> n;				// Universe range
	infile >> m;				// Number of subsets in family F
	k = atoi(argv[2]);			// Number of subsets to use for covering

	/* Validate parameters */

	if (n > 30) {
		cout	<< "Can't handle n > 30! Now exiting!"
			<< endl;
		return 1;
	}

	if (m > pow(2, n)) {
		cout	<< "Too many subsets. There can only be 2^n subsets of a n-sized set."
			<< endl;
		return 1;
	}

	if (k > m) {
		cout	<< "k > |F|. Can not pick more subsets than there are to pick from..."
			<< endl;
		return 1;
	}
	/* Initialize data structures */

	// The subset family F
	vector<int> family(m);		// m empty positions, all will be filled.

	// The function f, mapping from members of F to numbers in a ring R.
	// Each value x_i in the vector f is the function f's value corresponding to
	// the subset at the same index i in the vector family.
	vector<int> f(m);		// m empty positions, all will be filled.
	
	/* Construct data structures */

	for (int i = 0; i < m; ++i) {
		infile >> family[i];
		f[i] = 1;		// In k-cover, we use F's characteristic function
	}

	/* Initialize algorithm variables */

	int ck = 0;				// Number of k-covers.
	int n1, n2;				// Split of n

	/* Splitting n according to input decision */

	utils::pick_n2(&n1, &n2, m, n, split_decision);
	
	cout	<< "n1 = "	<< n1
		<< ", n2 = "	<< n2
		<< endl;

	/* Run the algorithm! */

	cout	<< "Calculating k-cover!"
		<< endl
		<< "===================="
		<< endl;

	k_cover_linear_space(n1, n2, &family, &f, k, &ck, split_decision);
	

	/* Output */
	
	cout	<< "===================="
		<< endl
		<< "Nbr of k-covers: " << ck 
		<< endl
		<< "Note: Different orderings and multiple pickings (if applicable) are also counted."
		<< endl;

	return 0;

	// Optimal factorial implementation
	// Values taken from Wolfram Alpha
	/*
	static const long factorial[16] = { 
		1, 
		1, 
		2, 
		6, 
		24, 
		120, 
		720,
		5040,
		40320,
		362880,
		3628800,
		39916800,
		479001600,
		6227020800,
		87178291200,
		1307674368000
	};
	
	if (k < 16) {
		cout 	<< k << "! = " << factorial[k] 
			<< " which means that without considering ordering, there are "
			<< (((long) ck) / factorial[k])
			<< " unique k-covers."
			<< endl;
	} else {
		cout	<< k << "! is too large to calculate."
			<< endl;
	}
	cout	<< "Note: Multiple pickings are allowed."
		<< endl;
	*/
}

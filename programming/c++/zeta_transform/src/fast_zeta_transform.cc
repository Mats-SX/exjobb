#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include "subset.h"
#include "bigint.h"
#include <bitset>

using namespace std;

void fast_zeta_transform_exp_space(int n, vector<int>* f) {	

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

void pick_n2(int* n1, int* n2, int f_size, int n, int split_decision) {

	switch (split_decision) {
		case -1:
			cout << "Default split of n used." << endl;
			*n2 = ceil(log2(f_size));
			break;
		case 1:
			cout << "Now we're using another way of splitting n." << endl;
			*n2 = n / 2;
			break;
	}
	*n1 = n - *n2;
	cout << "n1 = " << *n1 << ", n2 = " << *n2 << endl;

}


// We are assuming for now that the family F of subsets of U to be considered
// is ordered in Gray code order. That is, for each set X = {X1, X2, ..., Xk} in F,
// there is an index i = sum(2^(Xj - 1)) for j = 1, 2, ..., k, and the order
// of the sets X in F is in increasing order of their indices.
//
// family is a vector where the indices of sets in F are stored.
// f is a vector where the values of the function f in the algorithm
// are stored, each corresponding to a subset on same position in F.
void fast_zeta_transform_linear_space(int n, vector<int>* family, vector<int>* f, int split_decision = -1) {
	int n1;
	int n2;
	pick_n2(&n1, &n2, family->size(), n, split_decision);

	// Variables we only want to calculate once
	int two_to_the_n = pow(2, n);		// 2^n
	int two_to_the_n1 = pow(2, n1);		// 2^n1
	int two_to_the_n2 = pow(2, n2);		// 2^n2

	int u1 = two_to_the_n1 - 1;		// Index of U1 in the range of subsets 2^U
	int u2 = two_to_the_n - two_to_the_n1;	// Index of U2

	// Function g
	vector<int> g(two_to_the_n2);

	// DEBUG
	cout << "NOW STARTING THE MAIN LOOP" << endl << endl;

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
			// with index math: since u1 is all-ones,
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
		fast_zeta_transform_exp_space(n2, &g);

		// The vector g contains all subsets of U2, in increasing
		// order of index. But the indices of subsets of U2 doesn't come at
		// a distance of 1 from eachother, unlike with U1. They are separarated 
		// by 2^n1 positions.
		// {{ For each subset X2 of U2, output h(X2) as the value fS(X1uX2) }}
	
		
		for (int i = 0; i < two_to_the_n2; ++i) {
			int x2 = i * two_to_the_n1;

			
			cout << "fS(" << bitset<7>(x1 | x2) 
				<< " = " << (x1 | x2) 
				<< "): " << g[i] << endl;


			//(*f)[i] = g[i]; // WRONG NORMALIZATION!!
		}
	}

	return;
}



int main(int argc, char** argv) {

	ifstream infile(argv[1]);
	int n, m;
	infile >> n;
	infile >> m;
	
	cout << "This program is constrained to only handling n < 31 and function values "
		<< "f < 2^31.\n Larger values may cause the program to crash." << endl;
	if (n > 30) {
		cout << "Can't handle n > 30! Now exiting!" << endl;
		return 1;
	}

	vector<int> family(m);
	vector<int> f(m);
	
	int subset_index, f_val;
	for (int i = 0; i < m; ++i) {
		infile >> subset_index;
		infile >> f_val;
		family[i] = subset_index;
		f[i] = f_val;
	}


	
	// Input validation
	cout << "n: " << n << ", m: " << m << endl;
	for (int i = 0; i < f.size(); ++i) {
		cout << "f(" << bitset<7>(family[i]) << "): " << f[i] << endl;
	}
	
	
	fast_zeta_transform_linear_space(n, &family, &f);
	//fast_zeta_transform_exp_space(n, &f);

	
//	Transformed output
	/*
	for (int i = 0; i < f.size(); ++i) {
		cout << "fS(" << bitset<7>(i) << "): " << f[i] << endl;
	}
	*/
}

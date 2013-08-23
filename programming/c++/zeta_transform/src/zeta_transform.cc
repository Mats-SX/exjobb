#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include "subset.h"
#include "bigint.h"

using namespace std;

int main(int argc, char** argv) {

	ifstream infile(argv[1]);
	int n, m;
	infile >> n;
	infile >> m;

	Subset copy;
	vector<Subset> family(pow(2, n), copy);
	
	for (int i = 0; i < m; ++i) {
		BigInt* f_val = new BigInt();
		infile >> *f_val;
		Subset s(f_val);
		infile >> s;
		BigInt index;
		s.index_from_members(&index);
		cout << index << " <-- index\n";
		family[index.value()] = s;	// I do _not_ include all subsets, only those given.
	}

	/*
	for (vector<Subset*>::iterator it = family.begin();
		it != family.end(); ++it) {
		cout << **it << "\n";
	}*/

	/* This is where the magic happens */

	/* these are the n steps of the f
	   transform, using the same subsets
	   "behind the scenes". Each member of
	   the outer vector contains a list of
	   function values. */
	vector<vector<Subset> > f(n, family);
	/* 1. f_0 = f */
	f.push_back(family);
	/* 2. */
	for (int j = 1; j <= n; ++j) {
		/* PSEUDO
		for each subset X (in family)
			if (j in X)
				f_j(X) = f_j-1(X \ {j}) + f_j-1(X)
			else
				f_j(X) = f_j-1(X)
		*/
		for (int k = 0; k < f[j].size(); ++k) {
			if (f[j][k].is_empty())
				continue;
			if (f[j][k].contains(j)) {
				//cout << "Found a j" << endl;
				/* find X \ {j} somehow */
				BigInt b;
			       	f[j][k].index_from_members_without(j, &b);

				// Here we are likely to find NULL pointers (again)
				if (!f[j-1][b.value()].is_empty()) {
					cout << f[j][k] << endl;
					cout << "j is " << j << " and b is " << b.value() << endl;
					cout << "f[j-1][b] = "
					       	<< f[j-1][b.value()]
						<< " and f[j-1][k] = "
						<< f[j-1][k] 
						<< endl;
					f[j][k].setValue(
							*f[j-1][b.value()].getValue() + 
							*f[j-1][k].getValue());
				}
			} else {
				f[j][k].setValue(f[j-1][k].getValue());
			}
		}
	}
	/* 3. Output fS = f_n*/
	for (int i = 0; i < f[n-1].size(); ++i) {
		if (f[n-1][i].is_empty())
			continue;
		cout << f[n-1][i] << "\n";
	}

	// For reference, also output f_0
	for (int i = 0; i < f[n-1].size(); ++i) {
		if (f[n-1][i].is_empty())
			continue;
		cout << f[n-1][i] << "\n";
	}
	/* End of magic */

	// Clean up on the heap
	/*for (vector<Subset>::iterator it = family.begin();
		it != family.end(); ++it) {
		//delete *it;
	}*/
	return 0;
}

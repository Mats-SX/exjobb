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

	vector<Subset*> family(pow(2, n+1), NULL);
	
	for (int i = 0; i < m; ++i) {
		BigInt f_val;
		infile >> f_val;
		Subset* s = new Subset(f_val);
		infile >> *s;
		BigInt* index = s->index_from_members();
		cout << index->value << " <-- index\n";
		family[index->value] = s;	// This is cheating
	}
	/*
	for (vector<Subset*>::iterator it = family.begin();
		it != family.end(); ++it) {
		cout << **it << "\n";
	}*/

	/* This is where the magic happens */

	/* these are the n steps of the zeta
	   transform, using the same subsets
	   "behind the scenes". Each member of
	   the outer vector contains a list of
	   function values. */
	vector<vector<Subset*> > zeta(n, family);
	/* 1. f_0 = f */
	zeta.push_back(family);
	/* 2. */
	for (int j = 1; j <= n; ++j) {
		/* PSEUDO
		for each subset X (in family)
			if (j in X)
				f_j(X) = f_j-1(X \ {j}) + f_j-1(X)
			else
				f_j(X) = f_j-1(X)
		*/
		for (int k = 0; k < zeta[j].size(); ++k) {
			if (zeta[j][k] == NULL)
				continue;
			if (zeta[j][k]->contains(j)) {
				//cout << "Found a j" << endl;
				/* find X \ {j} somehow */
				
			} else {
				zeta[j][k]->value = zeta[j-1][k]->value;
			}
		}
	}
	/* 3. Output fS = f_n*/
	for (int i = 0; i < zeta[n-1].size(); ++i) {
		if (zeta[n-1][i] == NULL)
			continue;
		cout << *zeta[n-1][i] << "\n";
	}

	/* End of magic */

	// Clean up on the heap
	for (vector<Subset*>::iterator it = family.begin();
		it != family.end(); ++it) {
		delete *it;
	}
	return 0;
}

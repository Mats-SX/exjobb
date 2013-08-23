#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include "subset.h"
#include "bigint.h"

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


void fast_zeta_transform_linear_space(int n, vector<int>* family, vector<int>* f, int split_decision = -1) {
	int n1;
	int n2;
	
	switch (split_decision) {
		case -1:
			cout << "Default split of n used." << endl;
			n2 = ceil(log2(family->size()));
			n1 = n - n2;
			cout << "n1 = " << n1 << ", n2 = " << n2 << endl;
			break;
	}


	return;
}

int main(int argc, char** argv) {

	ifstream infile(argv[1]);
	int n;
	infile >> n;
	
	cout << "This program is constrained to only handling n < 31 and function values "
		<< "f < 2^31. Larger values may cause the program to crash." << endl;
	if (n > 30) {
		cout << "Can't handle n > 30! Now exiting!" << endl;
		return 1;
	}

	vector<int> f(pow(2, n));

	f[0] = 0;		// Empty set
	
	int f_val = 0;
	for (int i = 1; i < f.size(); ++i) {
		infile >> f_val;
		f[i] = f_val;
	}

	/*
	 * Input validation
	for (int i = 0; i < f.size(); ++i) {
		cout << "fS(" << i << "): " << f[i] << endl;
	}
	*/
	
	//vector<int> family(n/2);

	//fast_zeta_transform_linear_space(n, &family, NULL);
	fast_zeta_transform_exp_space(n, &f);

	/*
	 * Transformed output
	for (int i = 0; i < f.size(); ++i) {
		cout << "fS(" << i << "): " << f[i] << endl;
	}
	*/
}

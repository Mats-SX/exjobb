#include <iostream>
#include <fstream>
#include <bitset>
#include "utils.h"
#include "types.h"

using namespace std;

int main(int argc, char** argv) {

	if (argc != 2) {
		cout << "Supply exactly 1 argument, which is the infile." << endl;
		return 1;
	}

	ifstream infile(argv[1]);
	int_t n, m;
	infile >> n;
	infile >> m;
	
	cout << "This program is constrained to only handling n < 31 and function values "
		<< "f < 2^31.\n Larger values may cause the program to crash." << endl;
	if (n > 30) {
		cout << "Can't handle n > 30! Now exiting!" << endl;
		return 1;
	}

	int_list_t family(m);
	rval_list_t f(m);
	
	for (int i = 0; i < m; ++i) {
		infile >> family[i];
		infile >> f[i];
	}
	
	// Input validation
	/*
	cout << "n: " << n << ", m: " << m << endl;
	for (int i = 0; i < f.size(); ++i) {
		cout << "f(" << bitset<30>(family[i]) << "): " << f[i] << endl;
	}
	*/
	int_t n1, n2;

	int split = -1;

	utils::pick_n2(&n1, &n2, m, n, split);

	utils::fast_zeta_transform_linear_space(n1, n2, &family, &f);

	
//	Transformed output
	/*
	for (int i = 0; i < f.size(); ++i) {
		cout << "fS(" << bitset<7>(i) << "): " << f[i] << endl;
	}
	*/
}

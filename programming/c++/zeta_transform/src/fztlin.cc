#include <iostream>
#include <fstream>
#include <math.h>
#include <bitset>
#include <cstdlib>
#include "types.h"
#include "utils.h"
#include <gmp.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv) {

	/* Communication with user */

	cout 	<< "This is Fast Zeta Transform in linear space" << endl;
	
	int split = -1;
	
	cout	<< "Using default split." << endl;

	if (argc < 2) {
		cout 	<< "Usage: fztlin <infile>"
			<< endl;
		return 0;
	}

	/* Read parameters */

	ifstream infile(argv[1]);		// Streaming from provided file
	int_t n, m, k;
	infile >> n;				// Universe range
	infile >> m;				// Number of subsets in family F

	/* Initialize data structures */

	// The subset family F
	// m empty positions, all will be filled.
	int_list_t family(m);

	// The function f, mapping from members of F to members in a ring R.
	// Each value x_i in the vector f is the function f's value corresponding to
	// the subset at the same index i in the vector family.
	rval_list_t f(m);

	/* Construct data structures */

	for (int i = 0; i < m; ++i) {
		infile >> family[i];
		mpz_init(f[i]);
		int_t tmp;
		infile >> tmp;
		mpz_set_ui(f[i], tmp);
	}

	/* Initialize algorithm variables */

	int_t n1, n2;				// Split of n

	/* Splitting n according to input decision */

	utils::pick_n2(n1, n2, m, n, split);

	cout	<< "Parameters: " << endl
		<< "n: " << n << endl
		<< "|F|: " << m << endl
		<< "k: " << k << endl;

	cout	<< "n1 = "	<< n1
		<< ", n2 = "	<< n2
		<< endl;

	/* Run the algorithm! */

	cout	<< "Transforming!"
		<< endl
		<< "===================="
		<< endl;

	utils::fast_zeta_transform_linear_space(n1, n2, &family, &f);

	cout	<< "===================="
		<< endl;
	
	cout << endl;
	cout << "Now pausing for collection of statistics. PID is " << getpid() << endl;
	cout << "Kill me with 'kill -s 9 <PID>' if necessary" << endl;
	raise(SIGSTOP);

	return 0;
}

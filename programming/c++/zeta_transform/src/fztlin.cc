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
		split = atoi(argv[3]);
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

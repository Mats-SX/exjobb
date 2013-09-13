#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <bitset>
#include <cstdlib>
#include "utils.h"
#include "types.h"
#include <gmp.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;




int main(int argc, char** argv) {

	/* Communication with user */

	cout 	<< "This is k-packing."	<< endl;

	int split_decision = -1;
	if (argc == 3) {
		cout	<< "Using default split." 
			<< endl;
	} else if (argc != 4) {
		cout 	<< "Usage: k_packing <infile> <k> <split_decision>."
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
	int_t n, m, k;
	infile >> n;				// Universe range
	infile >> m;				// Number of subsets in family F
	k = atoi(argv[2]);			// Number of subsets to use for covering

	/* Validate parameters */

	if (k > m) {
		cout	<< "k > |F|. Can not pick more subsets than there are to pick from..."
			<< endl;
		return 1;
	}

	/* Initialize data structures */

	// The set family F
	int_list_t family(m);		// m empty positions, all will be filled.

	// The function f, mapping from members of F to numbers in a ring R.
	// Each value x_i in the vector f is the function f's value corresponding to
	// the set at the same index i in the vector family.
	rval_list_t f(m);		// m empty positions, all will be filled.
	
	/* Construct data structures */

	for (int_t i = 0; i < m; ++i) {
		infile >> family[i];
		// For k-partitioning, the function f(X)=z^p is a monomial of 
		// degree p equal to the size of the set, ie p = |X|, for X in F.
		int_t degree = utils::count_1bits(family[i]);
		f[i].set_degree(degree);
		mpz_set_ui(f[i][degree], 1);

		// DEBUG:
		//cout << "input p: " << p << endl;
	}

	/* Initialize algorithm variables */

	// Polynomial whose n-degree coefficient is the number of k-packings
	Polynomial pk;
	pk.set_degree(n);
	int_t n1, n2;			// Split of n

	/* Splitting n according to input decision */

	utils::pick_n2(n1, n2, m, n, split_decision);
	
	cout	<< "Parameters: " << endl
		<< "n: " << n << endl
		<< "|F|: " << m << endl
		<< "k: " << k << endl;	
	
	cout	<< "n1 = "	<< n1
		<< ", n2 = "	<< n2
		<< endl;

	/* Run the algorithm! */

	cout	<< "Calculating k-packing!"
		<< endl
		<< "===================="
		<< endl;

	utils::fast_zeta_transform_linear_space(n1, n2, &family, &f, k, &pk);
	

	/* Output */
	
	cout	<< "===================="
		<< endl
		<< "Nbr of k-packings: ~10^" << pk[n] 
		<< endl
		<< "Note: Different orderings are also counted."
		<< endl;

	cout << endl;
	cout << "Now pausing for collection of statistics. PID is " << getpid() << endl;
	cout << "Kill me with 'kill -s 9 <PID>' if necessary." << endl;
	raise(SIGSTOP);

	return 0;
}

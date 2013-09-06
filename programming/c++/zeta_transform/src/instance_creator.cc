#include <iostream>
#include <fstream>
#include <set>
#include <gmpxx.h>
#include <gmp.h>

using namespace std;

/*
 * Expected input: ofname
 * ofname: Name of output file.
 */
int main(int argc, char** argv) {

	cout << "Instance Creator for Fast Zeta Transform-based problems." << endl;

	if (argc < 2) {
		cout	<< "Too few arguments." << endl
			<< "Usage: ic <ofname>" << endl
			<< "Now exiting." << endl;
		return 0;
	}

	/* Parameters */

	mpz_class n, df;
	bool rvals = false;

	/* Read values */

	cout << "Universe size: ";
	cin >> n;
	cout << endl;

	cout << "Subset density (per thousand): ";
	cin >> df;
	cout << endl;

	cout << "Generate ring values? [0 means yes]: ";
	cin >> rvals;
	cout << endl;

	/* Tell user what's been read */

	cout	<< "Input given: n = " << n 
		<< ", df = " << df 
		<< ", rvals = " << rvals
		<< "." 
		<< endl;

	cout << "==========" << endl;

	/* Generate instance */

	cout << "Now generating instance ..." << endl;

	ofstream ofs(argv[1]);
	
	ofs << n << " " << df << endl;

	set<mpz_class> pool;
	mpz_class two_to_the_n;
	mpz_ui_pow_ui(two_to_the_n.get_mpz_t(), 2, n.get_ui());
	mpz_class f = (df * two_to_the_n) / 1000;

	gmp_randclass rand(gmp_randinit_default);
	
	while (pool.size() != f.get_ui()) {
		pool.insert(rand.get_z_range(two_to_the_n));
	}

	for (set<mpz_class>::iterator itr = pool.begin(); itr != pool.end(); ++itr) {
		ofs << (*itr);
		if (rvals) {
			ofs << " " << rand.get_z_range(two_to_the_n);
		}
		ofs << endl;
	}

	cout << pool.size() << " lines written to " << argv[1] << ". Bye bye." << endl;
	return 0;
}

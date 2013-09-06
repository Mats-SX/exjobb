#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <gmpxx.h>
#include <gmp.h>

using namespace std;

/*
 * Expected input: ifname
 * ifname: Name of input file.
 */
int main(int argc, char** argv) {

	cout << "Instance Creator for Fast Zeta Transform-based problems." << endl;

	if (argc < 2) {
		cout	<< "Too few arguments." << endl
			<< "Usage: ic <ifname>" << endl
			<< "Now exiting." << endl;
		return 0;
	}

	ifstream infile(argv[1]);
	
	int nbr_of_lines;
	bool rvals;
	infile >> nbr_of_lines;
	infile >> rvals;
	char* c_str = new char[50];
	infile.getline(c_str, 50);	// Get rid of the newline

	for (int i = 0; i < nbr_of_lines; ++i) {
		infile.getline(c_str, 50);	// The line is not supposed to be larger than 50 tokens
		string line(c_str);
		istringstream s(line);
		
		mpz_class n, df;
		s >> n;
		
		while (!s.eof()) {
			s >> df;

			/* Tell user what's been read */
			
			cout	<< "Input read: n = " << n 
				<< ", df = " << df 
				<< ", rvals = " << rvals
				<< "." 
				<< endl;
		
			cout << "==========" << endl;

			/* Generate instance */

			cout << "Now generating instance ..." << endl;

			stringstream outfile;
			outfile << "input/kp_" << n << "_" << df;
			ofstream ofs(outfile.str().c_str());
	
			set<mpz_class> pool;
			mpz_class two_to_the_n;
			mpz_ui_pow_ui(two_to_the_n.get_mpz_t(), 2, n.get_ui());
			mpz_class f = (df * two_to_the_n) / 1000;

			ofs << n << " " << f << endl;

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

			cout << pool.size() << " lines written to " << outfile.str() << ". Bye bye." << endl;
		}	
	}

	return 0;
}

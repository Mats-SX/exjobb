#include <iostream>
#include <fstream>
#include <math.h>
#include <set>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
	int n, f;

	cout << "Welcome to the Fast Zeta Transform in Linear Space instance generator!" << endl;
	cout << "This generator produces instances where n < 31 and all function values f(x) < 2^n" << endl;

	ostream* output_p;
	if (argc == 1) {
		cout << "Output will be given to stdout. "
			<< "If you would like to write to file, "
			<< "use syntax instance_creator <filename>." << endl;
		output_p = &cout;
	} else if (argc == 2) {
		cout << "Output will be given to file: " << argv[1] << endl;
		output_p = new ofstream(argv[1]);
	} else {
		cout << "Not a legal value for first argument!" << endl;
		return 1;
	}
	//ostream output = *output_p;
	//delete output_p;
	
	cout << "Please specify your universe range n = ";
	cin >> n;
	if (n > 31) {
		cout << "n > 31 not allowed!" << endl;
		return 1;
	}
	cout << "How many subsets would you like to include?\n f = ";
	cin >> f;

	cout << "Input given: n = " << n << ", f = " << f << "." << endl;

	cout << "\nNow generating sequence ..." << endl;

	(*output_p) << n << " " << f << endl;
	
	set<int> pool;
	int two_to_the_n = pow(2, n);

	while (pool.size() != f) {
		int r = rand() % two_to_the_n;
		pool.insert(r);
	}
	for (set<int>::iterator itr = pool.begin(); itr != pool.end(); ++itr) {
		int f_val = rand() % two_to_the_n;
		(*output_p) << (*itr) << " " << f_val << endl;
	}
}

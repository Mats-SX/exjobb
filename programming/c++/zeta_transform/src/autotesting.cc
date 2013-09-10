#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv) {
	
	cout << "This is autotesting." << endl;

	ifstream infile(argv[1]);	// Read what to test from file

	string prg;
	infile >> prg;

	int rows;
	infile >> rows;

	rusage usage;			// Same pointer for all tests

	for (int i = 0; i < rows; ++i) {
		int k;
		infile >> k;
	
		int nbr_of_tests;
		infile >> nbr_of_tests;

		for (int j = 0; j < nbr_of_tests; ++j) {
			string arg;
			infile >> arg;
			
			stringstream cmd;
			cmd 	<< prg << " "
				<< k << " input/"
				<< arg;

			cout << "Now running: " << cmd.str() << endl;
			
			getrusage(RUSAGE_SELF, &usage);
			double old_ut = (double) usage.ru_utime.tv_sec +
				(double) usage.ru_utime.tv_usec / 1000000.0;
			double old_st = (double) usage.ru_stime.tv_sec + 
				(double) usage.ru_stime.tv_usec / 1000000.0;
						
			system(cmd.str().c_str());

			getrusage(RUSAGE_SELF, &usage);
			
			double ut = (double) usage.ru_utime.tv_sec + 
				(double) usage.ru_utime.tv_usec / 1000000.0;
			double st = (double) usage.ru_stime.tv_sec + 
				(double) usage.ru_stime.tv_usec / 1000000.0;

			cout << "User time used: " << (ut - old_ut) << endl;
			cout << "System time used: " << (st - old_st) << endl;
			cout << "Total time used: " << (st + ut - old_ut - old_st) << endl;
		}

	}
	return 0;
}

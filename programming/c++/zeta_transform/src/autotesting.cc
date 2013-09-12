#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <ios>
#include <string>
#include <cstring>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//
// process_mem_usage(double &, double &) - takes five doubles by reference,
// attempts to read the system-dependent data for a process' virtual memory
// size and resident set size, and return the results in KB.
//
// On failure, returns 0.0, 0.0

void process_mem_usage(
		const pid_t& pid,
		double& vm_usage,
		double& resident_set,
		double& user_time,
		double& system_time,
		double& total_time)
{
	using std::ios_base;
	using std::ifstream;
	using std::string;

	vm_usage     = 0.0;
	resident_set = 0.0;

	// 'file' stat seems to give the most reliable results
	//
	stringstream s;
	s << "/proc/" << pid << "/stat";
	
	ifstream stat_stream(s.str().c_str(), ios_base::in);

	// dummy vars for leading entries in stat that we don't care about
	//
	string pid2, comm, state, ppid, pgrp, session, tty_nr;
	string tpgid, flags, minflt, cminflt, majflt, cmajflt;
	string cutime, cstime, priority, nice;
	string O, itrealvalue, starttime;

	// the fields we want
	//
	unsigned long vsize;
	long rss;
	unsigned long utime;
	unsigned long stime;

	stat_stream >> pid2 >> comm >> state >> ppid >> pgrp >> session >> tty_nr
	       	>> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
		>> utime >> stime >> cutime >> cstime >> priority >> nice
		>> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

	stat_stream.close();

	long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
	vm_usage	= vsize / 1024.0 / 1024.0;		// mB
	resident_set	= rss * page_size_kb / 1024.0;		// mB
	user_time	= (1000.0 * utime) / ((double) sysconf(_SC_CLK_TCK));	// milliseconds
	system_time	= (1000.0 * stime) / ((double) sysconf(_SC_CLK_TCK));	// milliseconds
	total_time	= user_time + system_time;
}


/*
 * Input file format:
 * <path to executable> <nbr of rows to follow>
 * <k> <nbr of values to follow> <file#1> <file#2> ... <file#n>
 * ...
 *
 *
 */
int main(int argc, char** argv) {
	
	cout << "This is autotesting." << endl;

	ifstream infile(argv[1]);	// Read what to test from file

	string prg;
	infile >> prg;

	int rows;
	infile >> rows;

	for (int i = 0; i < rows; ++i) {
		int k;
		infile >> k;
	
		int nbr_of_tests;
		infile >> nbr_of_tests;

		for (int j = 0; j < nbr_of_tests; ++j) {
			string arg;
			infile >> arg;

			stringstream cmd;
			cmd 	<< prg << " input/"
				<< arg << " "
				<< k; 

			cout << "Now running: " << cmd.str() << endl;

			char* args[4];
			char tmp[30];
		       	strcpy(tmp, cmd.str().c_str());
			
			args[0] = strtok(tmp, " ");
			for (int i = 1; i < 4; ++i) {
				args[i] = strtok(NULL, " ");
			}

			pid_t pid;
			switch((pid = fork())) {
				case -1:
				/* Fork failed */
				cerr << "Failed fork!" << endl;
				return 2;
				break;

				case 0:
				/* Let the child execute the test */
				execv(prg.c_str(), args);
				/* We will never get here (hopefully) */
				break;
			}

			/* Wait for child to finish before starting next */
			waitpid(pid, NULL, WUNTRACED);
			
			/* Measure child performance */
			double vm, rss, ut, st, tt;
			process_mem_usage(pid, vm, rss, ut, st, tt);
			
			/* Print stats */
			cout	<< "User time used:\t\t" << (ut) << " ms" 	<< endl
				<< "System time used:\t" << (st) << " ms"<< endl
				<< "Total time used:\t" << (tt) << " ms"	<< endl
				<< "Virtual Memory:\t\t" << vm << " MB"	<< endl
				<< "Resident set size:\t" << rss << " MB"<< endl;

			/* Let's proceed to next test. */
			
			cout << "#####################" << endl;

		}

	}
	return 0;
}

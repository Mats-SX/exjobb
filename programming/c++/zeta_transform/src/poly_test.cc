#include "polynomial.h"
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

	int deg1 = atoi(argv[1]);
	int deg2 = atoi(argv[2]);

	Polynomial p1(deg1);
	Polynomial p2(deg2);

	for (int i = 0; i <= deg1; i++) {
		p1.set_coeff_of_degree_to(i, rand() % 5);
	}
	for (int i = 0; i <= deg2; i++) {
		p2.set_coeff_of_degree_to(i, rand() % 5);
	}

	cout << "p1 = ";
	for (int i = 0; i <= p1.get_degree(); i++) {
		cout << p1.get_coeff_of_degree(i) << "x^" << i << " + ";
	}
	cout << endl;

	cout << "p2 = ";
	for (int i = 0; i <= p2.get_degree(); i++) {
		cout << p2.get_coeff_of_degree(i) << "x^" << i << " + ";
	}
	cout << endl;

	/* Test addition */
	p1 += p2;

	cout << "p1 + p2 = ";
	for (int i = 0; i <= p1.get_degree(); i++) {
		cout << p1.get_coeff_of_degree(i) << "x^" << i << " + ";
	}
	cout << endl;

	/* Test multiplication */
	p1 *= p2;

	cout << "(p1+p2) * p2 = ";
	for (int i = 0; i <= p1.get_degree(); i++) {
		cout << p1.get_coeff_of_degree(i) << "x^" << i << " + ";
	}
	cout << endl;


	/* Test taking power of */
	p1.raise_to_the(3);

	cout << "((p1+p2) * p2) ^ 3 = ";
	for (int i = 0; i <= p1.get_degree(); i++) {
		cout << p1.get_coeff_of_degree(i) << "x^" << i << " + ";
	}
	cout << endl;

	
	return 0;
}

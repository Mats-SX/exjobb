#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <gmp.h>

class Polynomial {
	friend std::ostream& operator<<(std::ostream&, const Polynomial&);
	public:
	Polynomial();
	~Polynomial();
	void operator+=(const Polynomial&);

	// Multiplies this polynomial with the parameter polynomial.
	// This method will not raise the degree of this polynomial.
	void operator*=(const Polynomial&);

	void operator*=(const int&);

	mpz_t& operator[](const int&);

	// This method will throw away all terms of higher degree.
	// It will not raise the degree of this polynomial.
	void raise_to_the(const int);
	
	void set_degree(const int);
	// No longer needed since we use ref-get on []
	//void set_coeff_of_degree_to(const int, const int);
	//void add_to_coeff_of_degree(const int, const int);
	//const int get_coeff_of_degree(const int) const;
	
	//const int get_degree() const;

	private:
	int degree;
	mpz_t* coeffs;
};

#endif

#include "polynomial.h"
#include <iostream>
#include <gmp.h>


Polynomial::Polynomial() { }

Polynomial::~Polynomial() {
	if (degree == 0) {
		delete coeffs;
		return;
	}
	for (int i = 0; i <= degree; ++i) {
		mpz_clear(coeffs[i]);
	}
	delete[] coeffs;
}

void Polynomial::operator+=(const Polynomial& term) {
	for (int i = 0; i <= term.degree; ++i) {
		mpz_add(coeffs[i], coeffs[i], term.coeffs[i]);
	}
	return;
}

void Polynomial::operator*=(const Polynomial& factor) {
	for (int i = degree; i > -1; --i) {
		mpz_t sum;
		mpz_init(sum);
		for (int j = 0; j <= i && j<= factor.degree; ++j) {
			mpz_addmul(sum, factor.coeffs[j], coeffs[i - j]);
		}
		mpz_set(coeffs[i], sum);
		mpz_clear(sum);
	}
}

void Polynomial::operator*=(const int& factor) {
	if (factor == 1)
		return;
	for (int i = 0; i <= degree; ++i) {
		mpz_mul_si(coeffs[i], coeffs[i], factor);
	}
}

mpz_t& Polynomial::operator[](const int& index) {
	return coeffs[index];
}

void Polynomial::raise_to_the(const int power) {
	if (power < 0)
		return;		// This is unsupported
	if (power  == 0) {
		for (int i = 1; i <= degree; ++i) {
			mpz_set_ui(coeffs[i], 0);
		}
		mpz_set_ui(coeffs[0], 1);
		return;
	}
	if (power == 1)
		return;

	// power >= 2
	
	// Make a copy p of this polynomial
	Polynomial p;
	p.set_degree(degree);
	for (int i = 0; i <= degree; ++i) {
		mpz_set(p[i], coeffs[i]);
	}

	for (int k = 1; k < power; ++k) {
		*this *= p;		// Multiply this with the copy power-1 times
	}
	
	return;
}

void Polynomial::set_degree(const int deg) {
	degree = deg;
	coeffs = new mpz_t[deg + 1];
	for (int i = 0; i <= degree; ++i) {
		mpz_init(coeffs[i]);
	}
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
	for (int i = 0; i <= p.degree; ++i) {
		os << p.coeffs[i] << "z^" << i << " + ";
	}
	os << std::endl;
	return os;
}

#include "polynomial.h"
#include <iostream>


Polynomial::Polynomial() {
	degree = 0;
	coeffs.resize(0);
}

Polynomial::Polynomial(const int deg) : degree(deg) {	
	coeffs.resize(deg + 1);		// polynomial of degree n has n+1 coefficients
}

void Polynomial::operator+=(const Polynomial& term) {
	if (degree < term.get_degree()) {
		for (int i = 0; i <= degree; ++i) {
			coeffs[i] += term.get_coeff_of_degree(i);
		}
		for (int i = degree + 1; i <= term.get_degree(); ++i) {
			coeffs.push_back(term.get_coeff_of_degree(i));
		}
		degree = term.get_degree();
	} else {
		for (int i = 0; i <= term.get_degree(); ++i) {
			coeffs[i] += term.get_coeff_of_degree(i);
		}
	}
	return;
}

void Polynomial::operator*=(const Polynomial& factor) {
	for (int i = degree; i > -1; --i) {
		int sum = 0;
		for (int j = 0; j <= i && j <= factor.degree; ++j) {
			sum += factor.coeffs[j] * coeffs[i-j];
		}
		coeffs[i] = sum;
	}
	return;
}

void Polynomial::operator*=(const int& factor) {
	if (factor == 1)
		return;
	for (int i = 0; i <= degree; ++i) {
		coeffs[i] *= factor;
	}
}

void Polynomial::add_to_coeff_of_degree(const int term, const int deg) {
	if (deg > degree || deg < 0) {
		return;
	}
	coeffs[deg] += term;
	return;
}

void Polynomial::raise_to_the(const int power) {
	if (power == 0) {
		degree = 0;
		coeffs.resize(0);
		return;
	}
	std::vector<int> sums(coeffs);
	for (int k = 1; k < power; ++k) {
		for (int i = degree; i > -1; --i) {
			int sum = 0;
			for (int j = 0; j <= i; ++j) {
				sum += coeffs[j] * sums[i-j];
			}
			sums[i] = sum;
		}
	}
	coeffs = sums;
	return;
}

void Polynomial::set_coeff_of_degree_to(const int deg, const int coeff) {
	if (deg > degree || deg < 0) {
		return;
	}
	/* DEBUG
	std::cout << "degree: " << degree << std::endl;
	std::cout << "deg: " << deg << std::endl;
	std::cout << "coeffs size: " << coeffs.size() << std::endl;
	*/
	coeffs[deg] = coeff;
	return;
}

const int Polynomial::get_coeff_of_degree(const int deg) const {
	if (deg > degree || deg < 0) {
		return 0;
	}
	return coeffs[deg];
}

const int Polynomial::get_degree() const {
	return degree;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
	for (int i = 0; i <= p.degree; ++i) {
		os << p.coeffs[i] << "z^" << i << " + ";
	}
	os << std::endl;
	return os;
}

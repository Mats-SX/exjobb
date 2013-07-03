#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>

class BigInt {
	friend std::istream& operator>>(std::istream&, BigInt&);
	friend std::ostream& operator<<(std::ostream&, const BigInt&);
	public:
	int value;
};

#endif

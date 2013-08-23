#ifndef BIGINT_H
#define BIGINT_H
#include <iostream>

class BigInt {
	friend std::istream& operator>>(std::istream&, BigInt&);
	friend std::ostream& operator<<(std::ostream&, const BigInt&);
	friend BigInt* operator+(BigInt&, BigInt&);
	public:
	BigInt();
	BigInt(const BigInt*);
	BigInt(int);
	BigInt(long);
	BigInt(long long);

	std::string toString();
	void add_two_power_of(int);
	int intValue();
	int value();	// This is cheating...

	private:
	int val;	//This is where we cheat so far.
};

#endif

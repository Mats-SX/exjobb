#include "bigint.h"
#include <math.h>

std::istream& operator>>(std::istream& is, BigInt& bigint) {
	is >> bigint.val;
	return is;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bigint) {
	os << "" << bigint.val << "\n";
	return os;
}

BigInt* operator+(BigInt& first, BigInt& snd) {
	// Let's pretend we are ints
	return new BigInt(first.val + snd.val);
}

BigInt::BigInt(const BigInt* other) {
	if (other == NULL)
		std::cout << "\n\nwtf" << std::endl;
	val = other->val;
}

void BigInt::add_two_power_of(int exp) {
	// This is also fake behaviour. Until we get the basic thing working, we'll live with it.
	val += pow(2, exp);
//	std::cout << "new value is " << value << std::endl;
}

int BigInt::intValue() {
	return val;
}

int BigInt::value() {
	return intValue();
}

std::string BigInt::toString() {
	return 0;
	//return static_cast<std::string>(val);
}

BigInt::BigInt() {
	// This is to where I've procastrinated all the tricky parts so far.
	// For a bit longer, we'll stick with fake BigInts (actual ints).
	val = 0;	
}

BigInt::BigInt(int value) {
	val = value;
}

BigInt::BigInt(long val) {

}

BigInt::BigInt(long long val) {

}

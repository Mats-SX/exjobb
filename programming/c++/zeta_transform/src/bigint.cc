#include "bigint.h"
#include <math.h>

std::istream& operator>>(std::istream& is, BigInt& bigint) {
	is >> bigint.value;
	return is;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bigint) {
	os << "" << bigint.value << "\n";
	return os;
}

void BigInt::add_two_power_of(int exp) {
	// This is also fake behaviour. Until we get the basic thing working, we'll live with it.
	value += pow(2, exp);
//	std::cout << "new value is " << value << std::endl;
}

BigInt::BigInt() {
	// This is to where I've procastrinated all the tricky parts so far.
	// For a bit longer, we'll stick with fake BigInts (actual ints).
	value = 0;	
}

BigInt::BigInt(int val) {

}

BigInt::BigInt(long val) {

}

BigInt::BigInt(long long val) {

}

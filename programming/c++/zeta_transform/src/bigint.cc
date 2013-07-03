#include "bigint.h"

std::istream& operator>>(std::istream& is, BigInt& bigint) {
	is >> bigint.value;
	return is;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bigint) {
	os << "" << bigint.value << "\n";
	return os;
}

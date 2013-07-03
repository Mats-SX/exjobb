#include "subset.h"
#include <string>
#include <algorithm>
#include <iterator>
#include "bigint.h"

Subset::Subset(BigInt val) {
	value = val;
	set = new std::set<BigInt*>();
}

Subset::~Subset() {
	for (std::set<BigInt*>::iterator it = set->begin(); it != set->end(); ++it) {
		delete *it;
	}
}

bool Subset::contains(int member) {
	return false;
}

void Subset::add_member(BigInt* member) {
	set->insert(member);
}

bool Subset::is_subset_of(Subset* other) {

}

bool Subset::is_superset_of(Subset* other) {

}

std::set<BigInt*> Subset::view_members() {

}

std::istream& operator>>(std::istream& is, Subset& subset) {
	while (true) {
		if (is.peek() == '\n') {
			is.get();
			return is;
		}
		BigInt* val = new BigInt();
		is >> *val;
		subset.add_member(val);
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Subset& subset) {
	os << "Subset with value " << subset.value << "\n";
	for (std::set<BigInt*>::iterator it = subset.set->begin();
			it != subset.set->end(); it++) {
		os << **it;
	}
	return os;
}

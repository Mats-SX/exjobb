#include "subset.h"
#include <string>
#include <algorithm>
#include <iterator>
#include "bigint.h"

Subset::Subset(BigInt* val) {
	value = val;
	set = new std::set<int>();
}

Subset::Subset(const Subset& other) {
	set = other.set;
	value = new BigInt(other.value);
}

bool Subset::is_empty() {
	return set->empty();
}

Subset::Subset() {
	value = new BigInt();
	set = new std::set<int>();
}

Subset::~Subset() {
/*	for (std::set<int>::iterator it = set->begin(); it != set->end(); ++it) {
		delete *it;
	}*/
}

void Subset::index_from_members_without(int j, BigInt* index) {
	for (std::set<int>::iterator it = set->begin(); it != set->end(); ++it) {
		if (*it == j)
			continue;
		//std::cout << "This member is " << *it << std::endl;
		index->add_two_power_of(*it - 1);
	}
}

void Subset::setValue(BigInt* value) {
	//delete (this->value);
	this->value = value;
}

BigInt* Subset::getValue() {
	return value;
}

void Subset::index_from_members(BigInt* index) {
	return index_from_members_without(-1, index);
}

bool Subset::contains(int member) {
	return set->find(member) != set->end();
}

void Subset::add_member(int member) {
	set->insert(member);
}

bool Subset::is_subset_of(Subset* other) {

}

bool Subset::is_superset_of(Subset* other) {

}
/*
std::set<BigInt*> Subset::view_members() {

}*/

std::istream& operator>>(std::istream& is, Subset& subset) {
	while (true) {
		if (is.peek() == '\n') {
			is.get();
			return is;
		}
//		BigInt* val = new BigInt();
//		is >> *val;
		int val = 0;
		is >> val;
		subset.add_member(val);
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Subset& subset) {
	os << "Subset with value " << *subset.value;
	for (std::set<int>::iterator it = subset.set->begin();
			it != subset.set->end(); it++) {
		os << *it << " ";
	}
	return os;
}

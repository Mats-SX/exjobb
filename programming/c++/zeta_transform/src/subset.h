#ifndef SUBSET_H
#define SUBSET_H

#include <set>
#include "bigint.h"

// It is expected that the members of a Subset will never exceed n
// Further, n is expected to fulfil n << 2^32. Hence, we can be satisfied
// with using ints as members of Subsets.

class Subset {
	friend std::istream& operator>>(std::istream& is, Subset& subset);
	friend std::ostream& operator<<(std::ostream& os, const Subset& subset);
	public:
	Subset(BigInt);
	~Subset();

	bool contains(int);
//	void add_member(BigInt*);
	void add_member(int);
	bool is_subset_of(Subset*);
	bool is_superset_of(Subset*);
//	std::set<BigInt*> view_members();
	BigInt value;
	BigInt* index_from_members();

	private:
//	std::set<BigInt*>* set;
	std::set<int>* set;
};


#endif

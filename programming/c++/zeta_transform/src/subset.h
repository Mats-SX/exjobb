#ifndef SUBSET_H
#define SUBSET_H

#include <set>
#include "bigint.h"

class Subset {
	friend std::istream& operator>>(std::istream& is, Subset& subset);
	friend std::ostream& operator<<(std::ostream& os, const Subset& subset);
	public:
	Subset(BigInt);
	~Subset();

	bool contains(int);
	void add_member(BigInt*);
	bool is_subset_of(Subset*);
	bool is_superset_of(Subset*);
	std::set<BigInt*> view_members();
	BigInt value;

	private:
	std::set<BigInt*>* set;
};


#endif

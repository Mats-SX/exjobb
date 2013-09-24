#ifndef TYPES_H
#define TYPES_H

#include "../../polynomial/polynomial.h"

typedef int int_t;
typedef Polynomial rval_t;

template <class T>
class PointerList {
	T* list;
	public:
	PointerList(const int s) {
		size = s;
		list = new T[s];
	}
	~PointerList() {
		delete[] list;
	}
	int_t size;
	T& operator[](const int i) { return list[i]; }
};

typedef PointerList<int_t> int_list_t;
typedef PointerList<rval_t> rval_list_t;

#endif

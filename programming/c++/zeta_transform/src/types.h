#ifndef TYPES_H
#define TYPES_H

#include "polynomial.h"

typedef int int_t;
<<<<<<< HEAD
typedef short rval_t;
=======
typedef char rval_t;
>>>>>>> Moved implementation of FZTlin to utils.

template <class T>
class PointerList {
	T* list;
	public:
	PointerList(const int s) {
		size = s;
		list = new T[s];
	}
<<<<<<< HEAD
	~PointerList() {
		delete[] list;
	}
=======
>>>>>>> Moved implementation of FZTlin to utils.
	int_t size;
	T& operator[](const int i) { return list[i]; }
};

typedef PointerList<int_t> int_list_t;
<<<<<<< HEAD
typedef PointerList<rval_t> rval_list_t;

=======
//typedef PointerList<Polynomial> pol_list_t;
typedef PointerList<rval_t> rval_list_t;

enum problem_t { k_cover, k_partition, k_packing };

>>>>>>> Moved implementation of FZTlin to utils.
#endif

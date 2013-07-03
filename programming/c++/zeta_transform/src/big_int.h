/**
	This is meant to be able to represent arbitrarily large integer
	numbers. It uses a dynamic list structure with one list node
	able to contain size_t bytes of the whole number. If all node
	values are appended, the whole integer is retrieved.
*/

#ifndef big_int_h
#define big_int_h

struct big_int_t {
	size_t part;
	big_int_t* next_part;
};

#endif

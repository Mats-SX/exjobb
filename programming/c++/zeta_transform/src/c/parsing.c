#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <stdbool.h>
#include "list.h"
#include "parsing.h"

void parse(FILE* input, list_t** subsets, int m) {
	for (int i = 0; i < m; ++i) {
		int* val = read_int(input);
//		printf("line value: %d\n", *val);
		list_t* subset = new_list(val);
		parse_line(input, subset);
		subsets[i] = subset;
	}
}

void parse_line(FILE* input, list_t* subset) {
	int* val;
	while (val = read_int(input)) {
//		printf("subset value: %d\n", *val);
		insert_first(subset, val);
	}
//	printf("loop is over!\n");
}

// For reading integers that fit in an int.
// Should be complemented with functions for reading larger
// integers.
// Disregards any number of leading whitespaces (isspace()
// determines this).
int* read_int(FILE* stream) {
	int integer = 0;
	int ascii = getc(stream);
	while (isspace(ascii))
		ascii = getc(stream);
	if (ascii == EOF) {
//		printf("reached end of file!\n");
		return NULL;
	}
	if (ascii == '#') {
//		printf("found the bracket!\n");
		return NULL;
	}
	while (isdigit(ascii)) {
		to_int(&ascii, &ascii);
		integer *= 10;
		integer += ascii;
		ascii = getc(stream);
	}
	int* i = malloc(sizeof(int));
	*i = integer;
//	printf("integer: %d\n", *i);
	return i;
}

// Only for decimal digits
void to_int(int* ascii, int* integer) {
	*integer = *ascii - 48;
}

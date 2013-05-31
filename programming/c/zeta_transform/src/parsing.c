#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
//#include <stdbool.h>
#include "list.h"
#include "parsing.h"

void parse(FILE* input, list_t** subsets, int m) {
	int val = 0;
	//fscanf(input, "%d", &val);
	for (int i = 0; i < m; ++i) {
		read_int(input, &val);
		printf("line value: %d\n", val);
		list_t* subset = new_list(&val);
		parse_line(input, subset);
		subsets[m] = subset;
	}
	//insert_first(subset, val);
//	return subset;
}

void parse_line(FILE* input, list_t* subset) {
	int val = 0;
	//read_int(input, &val);
	//fscanf(input, "%d", &val);
	//getc(input);
	//printf("function value: %d\n", val);
	while (read_int(input, &val)) {
//		list_t* element = new_list(val);
//		fscanf(input, "%d", &val);
//		read_int(input, &val);
		printf("subset value: %d\n", val);
		insert_first(subset, &val);
//		if (ferror(input))
//			continue;
//		getc(input); // skip next whitespace

	}
	printf("loop is over!\n");
}

// For reading integers that fit in an int.
// Should be complemented with functions for reading larger
// integers.
// Disregards any number of leading whitespaces (isspace()
// determines this).
bool read_int(FILE* stream, int* i) {
	int integer = 0;
	int ascii = getc(stream);
	while (isspace(ascii))
		ascii = getc(stream);
	if (ascii == EOF) {
		printf("reached end of file!\n");
		return false;
	}
	if (ascii == '#') {
		printf("found the bracket!\n");
		return false;
	}
	while (isdigit(ascii)) {
		to_int(&ascii, &ascii);
		integer *= 10;
		integer += ascii;
		ascii = getc(stream);
	}
	*i = integer;
//	printf("integer: %d\n", *i);
	return true;
}

// Only for decimal digits
void to_int(int* ascii, int* integer) {
	*integer = *ascii - 48;
}

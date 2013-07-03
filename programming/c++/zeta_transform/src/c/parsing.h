#ifndef parsing_h
#define parsing_h

#include <stdbool.h>

void parse(FILE*, list_t**, int);

void parse_line(FILE*, list_t*);

void to_int(int*, int*);

int* read_int(FILE*);

#endif

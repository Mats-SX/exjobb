#ifndef zeta_transform_h
#define zeta_transform_h

typedef struct subset_t subset_t;

struct subset_t {
	int f_value;
	list_t* nbrs;
};

list_t* parse(FILE*, int, int);

list_t* parse_line(FILE*);

#endif

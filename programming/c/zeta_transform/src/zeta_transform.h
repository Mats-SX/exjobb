#ifndef zeta_transform_h
#define zeta_transform_h

typedef struct list_t list_t;
typedef struct subset_t subset_t;

struct subset_t {
	int f_value;
	list_t* nbrs;
};

struct list_t {
	void* data;
	list_t* next;
};

list_t* parse(FILE*, int, int);

list_t* new_list(void*);

void free_list(list_t*);

void* getFirst(list_t*);

#endif

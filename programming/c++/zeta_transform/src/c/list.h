#ifndef list_h
#define list_h

typedef struct list_t list_t;

struct list_t {
	void* data;
	list_t* next;
};

list_t* new_list(void*);

void free_list(list_t*);

void destroy_lists(list_t**, int);

void insert_first(list_t*, void*);

void* getFirst(list_t*);

#endif

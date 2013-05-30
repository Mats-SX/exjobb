#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void* getFirst(list_t* list) {
	return list->data;
}

list_t* new_list(void* data) {
	list_t*	list;
	list = malloc(sizeof(list_t));
	list->data = data;
	list->next = NULL;
}

void insert(list_t* list, void* data) {
	return;
}

void free_list(list_t* list) {
	if (list->next == NULL) {
		free(list);
		return;
	} else {
		free_list(list->next);
		free(list);
	}
	return;
}

void insert_first(list_t* list, void* data) {
	list_t* l = new_list(data);
	l->next = list;
}

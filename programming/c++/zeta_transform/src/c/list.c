#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void* getFirst(list_t* list) {
	return list->data;
}

list_t* new_list(void* head) {
	list_t*	list = malloc(sizeof(list_t));
	list->data = head;
	list->next = NULL;
	return list;
}

void insert(list_t* list, void* data) {
	return;
}

void destroy_lists(list_t** lists, int nbr_of_lists) {
	for (int i = 0; i < nbr_of_lists; ++i) {
		free_list(lists[i]);
//		free(lists[i]);
	}
	free(lists);
}

void free_list(list_t* list) {
	if (list->next == NULL) {
		free(list->data);
		free(list);
	} else {
		free_list(list->next);
		free(list->data);
		free(list);
	}
	return;
}

void insert_first(list_t* list, void* data) {
	list_t* l = new_list(data);
	l->next = list->next;
	list->next = l;
}

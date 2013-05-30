#include <stdio.h>
#include <stdlib.h>
#include "zeta_transform.h"

int main(int argc, char** argv) {
	FILE* input = fopen(argv[1], "r");

	int n, m;
	fscanf(input, "%d%d\n", &m, &n);

	list_t* data_structure = parse(input, n, m);

	printf("%d\n", data_structure->data);
	printf("%s + %s\n", argv[0], argv[1]);
	printf("Hello world!\n");
	free_list(data_structure);
	fclose(input);
	return 0;
}

void* getFirst(list_t* list) {
	return list->data;
}


list_t* parse(FILE* input, int n, int m) {
	list_t* list = new_list(NULL);
	for (int i = 0; i < m; ++i) {
		int val;
		val = getc(input);
		printf("%d\n", val);
		list->data = val;
	}
	return list;
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

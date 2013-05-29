#include <stdio.h>
#include <stdlib.h>
#include "src/zeta_transform.h"

int main(int argc, char** argv) {
	FILE* input = fopen(argv[1], "r");

	int n, m;
	fscanf(input, "%d%d\n", &m, &n);

	list_t* data_structure = parse(input, n, m);

	printf("%d\n", data_structure->data);
	printf("%s + %s\n", argv[0], argv[1]);
	printf("Hello world!\n");
	return 0;
}

list_t* parse(FILE* input, int n, int m) {
	list_t* list = new_list(NULL);
	for (int i = 0; i < m; ++i) {
		int val;
		val = getc(input);
		printf("%d\n", val);
		list->data = val;
	}
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

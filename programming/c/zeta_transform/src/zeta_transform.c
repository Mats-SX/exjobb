#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "zeta_transform.h"

int main(int argc, char** argv) {
	FILE* input = fopen(argv[1], "r");

	int n, m;
	fscanf(input, "%d%d\n", &m, &n);
	printf("m: %d n: %d\n", m, n);
	list_t* data_structure = parse(input, n, m);

	printf("first element?: %d\n", data_structure->data);
	printf("%s + %s\n", argv[0], argv[1]);
	printf("Hello world!\n");
	free_list(data_structure);
	fclose(input);
	return 0;
}

list_t* parse(FILE* input, int n, int m) {
	int val = 0;
	fscanf(input, "%d", &val);
	printf("line value: %d\n", val);
	list_t* subset = new_list(NULL);
	for (int i = 0; i < m; ++i) {
		insert_first(subset, parse_line(input));
	}
	insert_first(subset, val);
	return subset;
}

list_t* parse_line(FILE* input) {
	int val = 0;
	fscanf(input, "%d", &val);
	printf("function value: %d\n", val);
	getc(input);
	list_t* subset = new_list(val);
	while (!feof(input) && !ferror(input)) {
		printf("subset value: %d\n", val);
		insert_first(subset, val);
		fscanf(input, "%d", &val);
		if (ferror(input))
			continue;
		getc(input);

	}
	return subset;
}

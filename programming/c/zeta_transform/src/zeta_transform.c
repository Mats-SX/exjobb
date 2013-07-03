#include <stdio.h>
#include <stdlib.h>
#include "list.h"
//#include "zeta_transform.h"
#include "parsing.h"

int main(int argc, char** argv) {
	FILE* input = fopen(argv[1], "r");

	int n = 0;
	int m = 0;
	fscanf(input, "%d%d\n", &n, &m);
//	printf("m: %d n: %d\n", m, n);

	list_t** data_structure =
			(list_t**) calloc(m, sizeof(list_t*));
	parse(input, data_structure, m);

	// No more input needed
	fclose(input);

	/* This is where the magic happens */

	

	/* End of magic */

	// Clean up on the heap
	destroy_lists(data_structure, m);
	return 0;
}

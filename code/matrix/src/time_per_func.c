// Print how long it takes to run a function on a matrix of various sizes, up to
// a maximum provided via command-line argument.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"

#define NUM_POINTS 100

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <max-size>\n", argv[0]);
		return 1;
	}

	int max_size = atoi(argv[1]);
	if (NUM_POINTS > max_size / 2) {
		fprintf(stderr, "NUM_POINTS must be less than MAX_SIZE / 2\n");
		return 1;
	}

	int size;
	printf("%d", NUM_POINTS);
	// guard for size > 0 to protect against overflow
	for (size = 1; size < max_size; size += max_size / NUM_POINTS) {
		clock_t begin = clock();
		matrix* m = matrix_new(size, size);
		printf(" %f", (double)(clock() - begin) / CLOCKS_PER_SEC);

		matrix_free(m);
	}
	printf("\n");

	return 0;
}

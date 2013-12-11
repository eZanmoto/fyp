// Print the largest matrix width/height, 2^n, for which constructing the matrix
// takes "negligible time" to construct.

#include <stdio.h>
#include <time.h>

#include "matrix.h"

#define MAX_DELAY 0.005

int main() {
	int i;
	double time = 0;

	// guard for i > 0 to protect against overflow
	for (i = 1; i > 0 && time < MAX_DELAY; i <<= 1) {
		clock_t begin = clock();
		matrix* m = matrix_new(i, i);
		time = (double)(clock() - begin) / CLOCKS_PER_SEC;

		matrix_free(m);
	}
	printf("%d\n", i >> 1);

	return 0;
}

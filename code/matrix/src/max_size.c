// Prints the largest matrix width/height of the form 2^k for which constructing
// and populating a matrix takes "negligible time". The maximum size considered
// is half the size of an unsigned integer.

#include <stdio.h>
#include <stdlib.h>

#include "lcg.h"
#include "timeout.h"

#include "matrix.h"

// Our definition of "negligible time" in milliseconds.
#define MAX_DELAY 10

int max = 1;

void print_max() {
	printf("%d\n", max >> 1);
	exit(0);
}

int main() {
	// Our implicit limit is MAX_UINT/2 = MAX_INT, which we break when `max`
	// overflows, i.e. when `max` < 0.
	while (max >= 0) {
		int size = max * max;
		lcg* lcg = lcg_new(size, 0);
		set_timeout(MAX_DELAY, print_max);
		matrix* m = matrix_new(max, max);

		int i;
		for (i = 0; i < size; i++) {
			unsigned int n = lcg_next(lcg);
			matrix_set(m, n / max, n % max, n);
		}
		clear_timeout();

		matrix_free(m);
		lcg_free(lcg);
		max <<= 1;
	}
	print_max();

	return 0;
}

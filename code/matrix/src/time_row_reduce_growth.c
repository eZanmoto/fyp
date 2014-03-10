// `time_row_reduce_s <size> <n>` prints the timing of `matrix_row_reduce()` on
// <n> fully-populated matrices of uniformly distributed sizes from 0 to <size>.

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "err.h"
#include "new.h"
#include "timer.h"

#include "matrix.h"

void fill(matrix* m) {
	int rows = matrix_num_rows(m);
	int i;
	for (i = 0; i < rows * matrix_num_cols(m); i++) {
		int next = i;
		matrix_set(m, next / rows, next % rows, (double) i);
	}
}

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <size> <n>\n", argv[0]);
		return 1;
	}
	int max_size = atoi(argv[1]);
	int n = atoi(argv[2]);
	printf("%d\n", n);

	timer* t = timer_new();
	int size, increment = max_size / n;
	ASSERT(increment > 0);
	for (size = 0; size < max_size; size += increment) {
		matrix* m = matrix_new(size, size);
		fill(m);

		timer_start(t);
		matrix_row_reduce(m);
		printf("%d %lu\n", size, timer_nsec(t));
		ASSERT(m);
		matrix_free(m);
	}

	return 0;
}

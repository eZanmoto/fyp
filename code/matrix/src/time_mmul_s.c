// `time_mmul_s <size> <n>` prints the timing of `matrix_mmul()` on <n>
// fully-populated matrices of uniformly distributed sizes from 0 to <size>.

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "err.h"
#include "lcg.h"
#include "new.h"
#include "timer.h"

#include "matrix.h"

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <size> <n>\n", argv[0]);
		return 1;
	}
	int max_size = atoi(argv[1]);
	int n = atoi(argv[2]);
	printf("%d %d\n", max_size, n);

	timer* t = timer_new();
	int size, i;
	for (size = 0; size < max_size; size += max_size / n) {
		matrix* m = matrix_new(size, size);
		int num_cells = size * size;
		lcg* lcg = lcg_new((unsigned int) num_cells, 0);
		for (i = 0; i < num_cells; i++) {
			int next = (int) lcg_next(lcg);
			matrix_set(m, next / size, next % size, (double) i);
		}

		timer_start(t);
		matrix_mmul(m, m);
		printf("%lu\n", timer_nsec(t));
		matrix_free(m);
	}

	return 0;
}

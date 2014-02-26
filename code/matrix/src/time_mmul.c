// `time_smul <size> <n>` populates a <size>x<size> matrix cell by cell and
// prints the timing of `matrix_smul()` on that matrix <n> times.

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "err.h"
#include "lcg.h"
#include "new.h"
#include "timer.h"

#include "matrix.h"

void expect(matrix *m, int row, int col, int expected) {
	int actual = matrix_get(m, row, col);
	if (actual != expected) {
		FATAL(2, "m[%d][%d] expected %d, got %d\n",
			row, col, expected, actual);
	}
}

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <size> <n>\n", argv[0]);
		return 1;
	}
	int size = atoi(argv[1]);
	int n = atoi(argv[2]);
	printf("%d %d\n", size, n);

	matrix* m = matrix_new(size, size);

	int num_cells = size * size;
	lcg* lcg = lcg_new(num_cells, 0);

	int print_interval = num_cells / n;
	int i;
	timer* t = timer_new();
	for (i = 0; i < num_cells; i++) {
		unsigned int next = lcg_next(lcg);
		int row =  next / size;
		int col = next % size;

		matrix_set(m, row, col, i);

		if (i % print_interval == 0) {
			timer_start(t);
			m = matrix_mmul(m, m);
			printf("%lu\n", timer_nsec(t));
		}
	}
	matrix_free(m);

	return 0;
}

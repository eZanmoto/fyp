// `time_mmul <size> <n>` populates a <size>x<size> matrix cell by cell and
// prints the timing of `matrix_mmul()` on that matrix <n> times.

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "err.h"
#include "new.h"
#include "timer.h"

#include "matrix.h"

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <size> <n>\n", argv[0]);
		return 1;
	}
	int size = atoi(argv[1]);
	int n = atoi(argv[2]);
	printf("%d\n", n);

	matrix* m = matrix_new(size, size);

	int num_cells = size * size;
	int print_interval = num_cells / n;
	int i;
	timer* t = timer_new();
	for (i = 0; i < num_cells; i++) {
		int next = i;
		int row =  next / size;
		int col = next % size;

		matrix_set(m, row, col, (double) i);

		if (i % print_interval == 0) {
			timer_start(t);
			m = matrix_mmul(m, m);
			printf("%2f %lu\n", ((i + 0.0) / num_cells) * 100, timer_nsec(t));
		}
	}
	matrix_free(m);

	return 0;
}

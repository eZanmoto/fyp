#include <stdio.h>

#include "matrix.h"

void matrix_fill(matrix* m) {
	int row, col;
	for (row = 0; row < matrix_num_rows(m); row++) {
		for (col = 0; col < matrix_num_cols(m); col++) {
			double val = row * matrix_num_cols(m) + col;
			matrix_set(m, row, col, val);
		}
	}
}

int main() {
	matrix* m1 = matrix_new(4, 3);
	matrix* m2 = matrix_new(3, 4);

	// 0 0 0 0    0  1  2
	// 0 0 0 0 -> 3  4  5
	// 0 0 0 0    6  7  8
	// 0 0 0 0    9 10 11
	matrix_fill(m1);

	// 0 0 0 0    0  1  2  3
	// 0 0 0 0 -> 4  5  6  7
	// 0 0 0 0    8  9 10 11
	matrix_fill(m2);

	matrix* m = matrix_mmul(m1, m2);

	// >    20.0     23.0     26.0     29.0
	// >    56.0     68.0     80.0     92.0
	// >    92.0    113.0    134.0    155.0
	// >   128.0    158.0    188.0    218.0
	printf("%s\n\n", matrix_str(m));

	matrix_free(m);

	return 0;
}

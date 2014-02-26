#include <stdio.h>

#include "matrix.h"

void matrix_fill(matrix* m) {
	int row, col;
	for (row = 0; row < matrix_num_rows(m); row++) {
		for (col = 0; col < matrix_num_cols(m); col++) {
			matrix_set(m, row, col, row * matrix_num_cols(m) + col);
		}
	}
}

matrix* matrix_id(int size) {
	matrix* id = matrix_new(size, size);
	int i;
	for (i = 0; i < size; i++) {
		matrix_set(id, i, i, 1);
	}
	return id;
}

int main() {
	matrix* m1 = matrix_new(4, 3);
	matrix* m2 = matrix_new(3, 4);
	// matrix* id = matrix_id(4);

	// 0 0 0 0    0  1  2
	// 0 0 0 0 -> 3  4  5
	// 0 0 0 0    6  7  8
	// 0 0 0 0    9 10 11
	matrix_fill(m1);

	// 0 0 0 0    0  1  2  3
	// 0 0 0 0 -> 4  5  6  7
	// 0 0 0 0    8  9 10 11
	matrix_fill(m2);

	//  20  23  26  29
	//  56  68  80  92
	//  92 113 134 155
	// 128 158 188 218
	matrix* m = matrix_mmul(m1, m2);

	// No change
	// matrix_mmul(m, id);

	printf("%s\n\n", matrix_str(m));

	matrix_free(m);

	return 0;
}

// Provides general matrix-based operations which are independent of the matrix
// implementation.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

#include "err.h"
#include "new.h"

char* matrix_str(matrix* m) {
	char* str;
	NEW(str, 1024);
	int len = 0;

	int i, j;
	for (i = 0; i < matrix_num_rows(m); i++) {
		for (j = 0; j < matrix_num_cols(m); j++) {
			double v = matrix_get(m, i, j);
			// Convert -0 to 0
			sprintf(str + len, "%8.1f ", v == 0 ? 0 : v);
			len += strlen(str + len);
		}
		str[len - 1] = '\n'; // replace the last space with a newline
	}
	str[len - 1] = '\0'; // replace the last newline with a string terminator

	return str;
}

matrix* matrix_aug(matrix* a, matrix* b) {
	ASSERT(matrix_num_rows(a) == matrix_num_rows(b));

	int row, col, mid = matrix_num_cols(a);
	matrix* aug = matrix_new(matrix_num_rows(a), mid + matrix_num_cols(b));
	for (row = 0; row < matrix_num_rows(aug); row++) {
		for (col = 0; col < matrix_num_cols(aug); col++) {
			bool in_b = mid <= col;
			matrix_set(aug, row, col,
				matrix_get(in_b ? b : a, row, col - mid * in_b));
		}
	}
	return aug;
}

void matrix_swap_rows(matrix* m, int a, int b) {
	int col;
	for (col = 0; col < matrix_num_cols(m); col++) {
		double tmp = matrix_get(m, a, col);
		matrix_set(m, a, col, matrix_get(m, b, col));
		matrix_set(m, b, col, tmp);
	}
}

void matrix_row_smul(matrix* m, int row, double x) {
	int col;
	for (col = 0; col < matrix_num_cols(m); col++) {
		matrix_set(m, row, col, matrix_get(m, row, col) * x);
	}
}

void matrix_add(matrix* m, int row, int col, double val) {
	matrix_set(m, row, col, matrix_get(m, row, col) + val);
}

void matrix_elim(matrix* m, int row, int col) {
	int row_, col_;
	for (row_ = 0; row_ < matrix_num_rows(m); row_++) {
		if (row_ != row && matrix_get(m, row_, col)) {
			double a = matrix_get(m, row_, col);
			for (col_ = 0; col_ < matrix_num_cols(m); col_++) {
				matrix_add(m, row_, col_,
					-(a * matrix_get(m, row, col_)));
			}
			matrix_set(m, row_, col, 0.0);
		}
	}
}

// Adapted in large from the clean and well-documented implementation of
// Gauss-Jordan elimination at
//
//     http://ic.ucsc.edu/~ptantalo/math21/Winter07/GaussJordan.java
void matrix_row_reduce(matrix* m) {
	int row, col;
	row = col = 0;
	while (row < matrix_num_rows(m) && col < matrix_num_cols(m)) {
		int row_ = row;
		while (row_ < matrix_num_rows(m) && !matrix_get(m, row_, col)) {
			row_++;
		}

		if (row_ < matrix_num_rows(m)) {
			if (row_ != row) {
				matrix_swap_rows(m, row, row_);
			}

			if(!matrix_get(m, row, col)) {
				matrix_free(m);
				m = NULL;
				return;
			}

			matrix_row_smul(m, row, 1 / matrix_get(m, row, col));

			matrix_elim(m, row, col);
			row++;
		}

		col++;
	}
}

matrix* matrix_inv(matrix* m) {
	ASSERT(matrix_num_rows(m) == matrix_num_cols(m));

	int row, col, w = matrix_num_rows(m);

	matrix* id = matrix_new(w, w);
	for (row = 0; row < w; row++) {
		matrix_set(id, row, row, 1.0);
	}

	matrix* aug = matrix_aug(m, id);
	matrix_row_reduce(aug);
	if (!aug) {
		matrix_free(id);
		return NULL;
	}

	matrix* b = id; // Recycle the memory allocated to `id`
	for (row = 0; row < w; row++) {
		for (col = 0; col < w; col++) {
			matrix_set(b, row, col, matrix_get(aug, row, w + col));
		}
	}
	matrix_free(aug);

	return b;
}

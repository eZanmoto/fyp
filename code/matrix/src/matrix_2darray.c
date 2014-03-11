// A 2-dimensional array-based implementation of the `matrix.h` interface.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

#include "err.h"
#include "new.h"

struct _matrix {
	double** rows;
	int num_rows;
	int num_cols;
};

matrix* matrix_new(int num_rows, int num_cols) {
	matrix* m = malloc(sizeof(matrix));
	NEW(m->rows, (unsigned long) num_rows);
	int i;
	for (i = 0; i < num_rows; i++) {
		NEW(m->rows[i], (unsigned long) num_cols);
	}
	m->num_rows = num_rows;
	m->num_cols = num_cols;

	// Allocated memory is not guaranteed to be zeroed out, but that is a
	// promise made by this function.
	matrix_smul(m, 0.0);

	return m;
}

int matrix_num_rows(matrix* m) {
	return m->num_rows;
}

int matrix_num_cols(matrix* m) {
	return m->num_cols;
}

void matrix_free(matrix* m) {
	int i;
	for (i = 0; i < m->num_rows; i++) {
		free(m->rows[i]);
	}
	free(m->rows);
	free(m);
}

void matrix_set(matrix* m, int row, int col, double val) {
	m->rows[row][col] = val;
}

void matrix_smul(matrix* m, double x) {
	int i, j;
	for (i = 0; i < matrix_num_rows(m); i++) {
		for (j = 0; j < matrix_num_cols(m); j++) {
			m->rows[i][j] *= x;
		}
	}
}

double matrix_get(matrix* m, int row, int col) {
	return m->rows[row][col];
}

matrix *matrix_mmul(matrix* m1, matrix* m2) {
	ASSERT(matrix_num_cols(m1) == matrix_num_rows(m2));

	matrix* m = matrix_new(matrix_num_rows(m1), matrix_num_cols(m2));

	int row, col, i;
	for (row = 0; row < matrix_num_rows(m); row++) {
		for (col = 0; col < matrix_num_cols(m); col++) {
			double sum = 0;
			for (i = 0; i < matrix_num_cols(m1); i++) {
				sum += matrix_get(m1, row, i) *
					matrix_get(m2, i, col);
			}
			matrix_set(m, row, col, sum);
		}
	}

	return m;
}

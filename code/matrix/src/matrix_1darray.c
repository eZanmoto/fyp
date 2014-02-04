// A 1-dimensional array-based implementation of the `matrix.h` interface.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

struct _matrix {
	int* rows;
	int num_rows;
	int num_cols;
};

matrix* matrix_new(int num_rows, int num_cols) {
	matrix* m = malloc(sizeof(matrix));
	m->rows = malloc(sizeof(int) * num_rows * num_cols);
	m->num_rows = num_rows;
	m->num_cols = num_cols;

	// Allocated memory is not guaranteed to be zeroed out, but that is a
	// promise made by this function.
	matrix_smul(m, 0);

	return m;
}

int matrix_num_rows(matrix* m) {
	return m->num_rows;
}

int matrix_num_cols(matrix* m) {
	return m->num_cols;
}

void matrix_free(matrix* m) {
	free(m->rows);
	free(m);
}

int* matrix_at(matrix* m, int row, int col) {
	return &(m->rows[row * matrix_num_cols(m) + col]);
}

void matrix_set(matrix* m, int row, int col, int val) {
	*matrix_at(m, row, col) = val;
}

void matrix_smul(matrix* m, int x) {
	int i, j;
	for (i = 0; i < matrix_num_rows(m); i++) {
		for (j = 0; j < matrix_num_cols(m); j++) {
			*matrix_at(m, i, j) *= x;
		}
	}
}

int matrix_get(matrix* m, int row, int col) {
	return *matrix_at(m, row, col);
}

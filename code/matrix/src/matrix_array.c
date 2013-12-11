// An array-based implementation of the `matrix.h` interface.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

struct _matrix {
	int** rows;
	int num_rows;
	int num_cols;
};

matrix* matrix_new(int num_rows, int num_cols) {
	matrix* m = malloc(sizeof(matrix));
	m->rows = malloc(sizeof(int*) * num_rows);

	int i;
	for (i = 0; i < num_rows; i++) {
		m->rows[i] = malloc(sizeof(int) * num_cols);

		// Allocated memory is not guaranteed to be zeroed out, but that is a
		// promise made by this function.
		int j;
		for (j = 0; j < num_cols; j++) {
			m->rows[i][j] = 0;
		}
	}

	m->num_rows = num_rows;
	m->num_cols = num_cols;
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
	free(m);
}

void matrix_set(matrix* m, int row, int col, int val) {
	m->rows[row][col] = val;
}

int matrix_get(matrix* m, int row, int col) {
	return m->rows[row][col];
}

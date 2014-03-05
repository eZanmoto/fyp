// A linked-list-based implementation of the `matrix.h` interface.

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

#include "err.h"

typedef struct matrix_cell {
	double value;
	struct matrix_cell* left;
	int row;
	int col;
} matrix_cell;

struct _matrix {
	matrix_cell** rows;
	int num_rows;
	int num_cols;
};

matrix_cell* matrix_cell_new(double val, matrix_cell* left, int row, int col) {
	matrix_cell* c = malloc(sizeof(matrix_cell));

	c->value = val;
	c->left = left;
	c->row = row;
	c->col = col;

	return c;
}

// Rows end with a sentinel cell whose column is `-1` to simplify some
// algorithms, such as the `while (col < before->left->col)` loop in
// `matrix_set`.
matrix* matrix_new(int num_rows, int num_cols) {
	matrix* m = malloc(sizeof(matrix));
	m->num_rows = num_rows;
	m->num_cols = num_cols;

	int i;
	m->rows = malloc(sizeof(matrix_cell*) * num_rows);
	for (i = 0; i < num_rows; i++) {
		m->rows[i] = matrix_cell_new(0.0, NULL, i, -1);
		m->rows[i]->left = m->rows[i];
	}

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
		matrix_cell* cur = m->rows[i]->left;
		while (-1 < cur->col) {
			matrix_cell* next = cur->left;
			// free(cur);
			cur = next;
		}
		// free(cur);
	}
	// free(m->rows);
	// free(m);
}

void matrix_set(matrix *m, int row, int col, double val) {
	matrix_cell* before = m->rows[row];
	while (col < before->left->col) {
		before = before->left;
	}

	if (before->left->col == col) {
		matrix_cell* c = before->left;
		if (val == 0) {
			before->left = c->left;
			free(c);
		} else {
			c->value = val;
		}
	} else if (val != 0) {
		matrix_cell* c = matrix_cell_new(val, before->left, row, col);
		before->left = c;
	}
	// Don't do anything if `val` == 0 and cell doesn't exist
}

void matrix_smul(matrix* m, double x) {
	if (x == 0) {
		int rows = matrix_num_rows(m);
		int cols = matrix_num_cols(m);
		matrix_free(m);
		m = matrix_new(rows, cols);
	} else {
		int row;
		for (row = 0; row < matrix_num_rows(m); row++) {
			matrix_cell* cur = m->rows[row]->left;
			while (-1 < cur->col) {
				cur->value *= x;
				cur = cur->left;
			}
		}
	}
}

double matrix_get(matrix* m, int row, int col) {
	matrix_cell* c = m->rows[row]->left;
	while (col < c->col) {
		c = c->left;
	}
	return c->col == col ? c->value : 0;
}

// FIXME very inefficient at the moment
matrix* matrix_mmul(matrix* m1, matrix* m2) {
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

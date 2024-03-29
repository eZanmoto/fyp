// A linked-list-based implementation of the `matrix.h` interface.

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

#include "err.h"

typedef struct matrix_cell {
	double value;
	struct matrix_cell* up;
	struct matrix_cell* left;
	int row;
	int col;
} matrix_cell;

struct _matrix {
	matrix_cell** rows;
	matrix_cell** cols;
	int num_rows;
	int num_cols;
};

matrix_cell* matrix_cell_new(double val, matrix_cell* up, matrix_cell* left,
		int row, int col) {
	matrix_cell* c = malloc(sizeof(matrix_cell));

	c->value = val;
	c->up = up;
	c->left = left;
	c->row = row;
	c->col = col;

	return c;
}

matrix* matrix_new(int num_rows, int num_cols) {
	matrix* m = malloc(sizeof(matrix));
	m->num_rows = num_rows;
	m->num_cols = num_cols;
	int i;

	m->rows = malloc(sizeof(matrix_cell*) * (unsigned long)num_rows);
	for (i = 0; i < num_rows; i++) {
		m->rows[i] = matrix_cell_new(0.0, NULL, NULL, i, -1);
		m->rows[i]->left = m->rows[i];
	}

	m->cols = malloc(sizeof(matrix_cell*) * (unsigned long)num_cols);
	for (i = 0; i < num_cols; i++) {
		m->cols[i] = matrix_cell_new(0.0, NULL, NULL, -1, i);
		m->cols[i]->up = m->cols[i];
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
		m->rows[i]->left = NULL;
		while (cur != NULL) {
			matrix_cell* next = cur->left;
			free(cur);
			cur = next;
		}
	}
	for (i = 0; i < m->num_cols; i++) {
		free(m->cols[i]);
	}
	free(m);
}

void matrix_set(matrix *m, int row, int col, double val) {
	ASSERT(0 <= row);
	ASSERT(row < matrix_num_rows(m));
	ASSERT(0 <= col);
	ASSERT(col < matrix_num_cols(m));

	matrix_cell* before = m->rows[row];
	matrix_cell* below = m->cols[col];

	// will exit when we hit start because `m->rows[row]->col` = -1 and
	// `col` is non-negative.
	while (col < before->left->col) {
		before = before->left;
	}

	// same reasoning as above.
	while (row < below->up->row) {
		below = below->up;
	}

	if (before->left->col == col) {
		matrix_cell* c = before->left;
		ASSERT(below->up == c);
		if (val == 0) {
			before->left = c->left;
			below->up = c->up;
			free(c);
		} else {
			c->value = val;
		}
	} else if (val != 0) {
		matrix_cell* c = matrix_cell_new(val, below->up, before->left, row, col);
		before->left = c;
		below->up = c;
	}
	// Don't do anything if `val` == 0 and cell doesn't exist
}

void matrix_smul(matrix* m, double x) {
	if (x == 0) {
		int rows = matrix_num_rows(m);
		int cols = matrix_num_cols(m);
		free(m);
		m = matrix_new(rows, cols);
	} else {
		int row;
		for (row = 0; row < matrix_num_rows(m); row++) {
			matrix_cell* cur = m->rows[row]->left;
			while (cur->col > -1) {
				cur->value *= x;
				cur = cur->left;
			}
		}
	}
}

double matrix_get(matrix* m, int row, int col) {
	ASSERT(0 <= row);
	ASSERT(row < matrix_num_rows(m));
	ASSERT(0 <= col);
	ASSERT(col < matrix_num_cols(m));

	matrix_cell* c = m->rows[row]->left;
	// will exit when we hit start because `m->rows[row]->col` = -1 and
	// `col` is non-negative.
	while (col < c->col) {
		c = c->left;
	}
	return c->col == col ? c->value : 0;
}

matrix* matrix_mmul(matrix* m1, matrix* m2) {
	ASSERT(matrix_num_cols(m1) == matrix_num_rows(m2));

	matrix* m = matrix_new(matrix_num_rows(m1), matrix_num_cols(m2));

	int row, col;
	for (row = 0; row < matrix_num_rows(m); row++) {
		for (col = 0; col < matrix_num_cols(m); col++) {
			matrix_cell* c1 = m1->rows[row]->left;
			matrix_cell* c2 = m2->cols[col]->up;

			double sum = 0;
			while (c1->col >= 0 && c2->row >= 0) {
				if (c1->col == c2->row) {
					sum += c1->value * c2->value;
					c1 = c1->left;
					c2 = c2->up;
				} else if (c1->col > c2->row) {
					c1 = c1->left;
				} else {
					c2 = c2->up;
				}
			}

			// This should give a O(1) insertion time since we're
			// inserting an earlier element every time.
			matrix_set(m, row, col, sum);
		}
	}

	return m;
}

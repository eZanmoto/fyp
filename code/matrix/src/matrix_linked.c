// A linked-list-based implementation of the `matrix.h` interface.

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

// `matrix_cell`
typedef struct matrix_cell {
	int value;
	struct matrix_cell* up;
	struct matrix_cell* left;
	int row;
	int col;
} matrix_cell;

// 2D array-based matrix
struct _matrix {
	matrix_cell** rows;
	matrix_cell** cols;
	int num_rows;
	int num_cols;
};

matrix_cell* matrix_cell_new(int val, matrix_cell* up, matrix_cell* left,
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

	m->rows = malloc(sizeof(matrix_cell*) * num_rows);
	for (i = 0; i < num_rows; i++) {
		m->rows[i] = matrix_cell_new(0, NULL, NULL, i, -1);
		m->rows[i]->left = m->rows[i];
	}

	m->cols = malloc(sizeof(matrix_cell*) * num_cols);
	for (i = 0; i < num_cols; i++) {
		m->cols[i] = matrix_cell_new(0, NULL, NULL, -1, i);
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
}

void matrix_set(matrix *m, int row, int col, int val) {
	if (row >= m->num_rows || col >= m->num_cols) {
		perror("cell out of range");
		exit(1);
	}

	matrix_cell* before = m->rows[row];

	// will exit when we hit start, as m->rows[row]->col == -1, and !(-1 > col)
	while (before->left->col > col) {
		before = before->left;
	}

	if (before->left->col == col) {
		before->left->value = val;
	} else {
		matrix_cell* below = m->cols[col];
		while (below->up->row > row) {
			below = below->up;
		}

		matrix_cell* c = matrix_cell_new(val, below->up, before->left, row, col);
		before->left = c;
		below->up = c;
	}
}

int matrix_get(matrix* m, int row, int col) {
	matrix_cell* c = m->rows[row]->left;
	// will exit when we hit start, as m->rows[row]->col == -1, and !(-1 > col)
	while (col < c->col) {
		c = c->left;
	}
	return c->col == col ? c->value : 0;
}

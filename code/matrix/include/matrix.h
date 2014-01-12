/**
 * \file matrix.h
 * \brief Provides methods for interfacing with a matrix implementation.
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

/**
 * \brief Forward declaration of structure so members aren't exposed.
 */
struct _matrix;

/**
 * \brief A 2-dimensional matrix containing integers.
 */
typedef struct _matrix matrix;

/** 
 * \brief Return a new matrix.
 *
 * All cells are initialized to 0.
 */
matrix* matrix_new(int num_rows, int num_cols);

/**
 * \brief The number of rows in `m`.
 */
int matrix_num_rows(matrix* m);

/**
 * \brief The number of columns in `m`.
 */
int matrix_num_cols(matrix* m);

/** 
 * \brief Set the value of `m` at cell (`row`, `col`) to `val`.
 */
void matrix_set(matrix* m, int row, int col, int val);

/** 
 * \brief Return the value of `m` at cell (`row`, `col`).
 */
int matrix_get(matrix* m, int row, int col);

/**
 * \brief Free the memory allocated to `m`.
 */
void matrix_free(matrix* m);

/**
 * \brief Return a string representation of `m`.
 */
char *matrix_str(matrix* m);

#endif
/**
 * \file matrix.h
 * \brief Provides methods for interfacing with a matrix implementation.
 *
 * `void` functions that take a `matrix*` as their first parameter modify the
 * matrix in place. Functions that return `matrix*` don't modify their
 * parameters, but instead return a new matrix as the result.
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

// Forward declaration of structure so members aren't exposed.
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
void matrix_set(matrix* m, int row, int col, double val);

/** 
 * \brief Return the value of `m` at cell (`row`, `col`).
 */
double matrix_get(matrix* m, int row, int col);

/** 
 * \brief Multiply `m` by the scalar `x`.
 */
void matrix_smul(matrix* m, double x);

/**
 * \brief Multiply the matrix `m1` with the matrix `m2`.
 */
matrix* matrix_mmul(matrix* m1, matrix* m2);

/**
 * \brief Free the memory allocated to `m`.
 */
void matrix_free(matrix* m);

/**
 * \brief Augment `b` to the right of `a`.
 *
 * `a` and `b` must have the same number of rows.
 */
matrix* matrix_aug(matrix* a, matrix* b);

/**
 * \brief Reduce `m` to row reduced echelon form, or `NULL` if `m` is singular.
 */
void matrix_row_reduce(matrix* m);

/**
 * \brief The inverse of `m`.
 *
 * `m` must be square.
 */
matrix* matrix_inv(matrix* m);

/**
 * \brief Return a string representation of `m`.
 */
char *matrix_str(matrix* m);

#endif

// Provides general matrix-based operations which are independent of the matrix
// implementation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

char* matrix_str(matrix* m) {
	char* str = malloc(1024);
	int len = 0;

	int i, j;
	for (i = 0; i < matrix_num_rows(m); i++) {
		for (j = 0; j < matrix_num_cols(m); j++) {
			sprintf(str + len, "%d ", matrix_get(m, i, j));
			len += strlen(str + len);
		}
		str[len - 1] = '\n'; // replace the last space with a newline
	}
	str[len - 1] = '\0'; // replace the last newline with a string terminator

	return str;
}

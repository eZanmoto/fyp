#include <stdio.h>

#include "matrix.h"

int main() {
	matrix* m = matrix_new(3, 4);

	// 0 0 0 0    0 0 0 0
	// 0 0 0 0 -> 3 0 0 0
	// 0 0 0 0    0 0 0 0
	matrix_set(m, 1, 0, 3);
	printf("%s\n\n", matrix_str(m));

	// 0 0 0 0    0 0 0 0
	// 3 0 0 0 -> 3 0 0 0
	// 0 0 0 0    0 0 0 4
	matrix_set(m, 2, 3, 4);
	printf("%s\n", matrix_str(m));

	matrix_free(m);

	return 0;
}

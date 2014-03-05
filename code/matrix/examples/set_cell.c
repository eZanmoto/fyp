#include <stdio.h>

#include "matrix.h"

int main() {
	matrix* m = matrix_new(3, 4);

	matrix_set(m, 1, 1, 3.0);
	// >     0.0      0.0      0.0      0.0
	// >     0.0      3.0      0.0      0.0
	// >     0.0      0.0      0.0      0.0
	// >
	printf("%s\n\n", matrix_str(m));

	matrix_set(m, 2, 3, 4.0);
	// >     0.0      0.0      0.0      0.0
	// >     0.0      3.0      0.0      0.0
	// >     0.0      0.0      0.0      4.0
	// >
	printf("%s\n\n", matrix_str(m));

	matrix_set(m, 1, 0, 2.0);
	// >     0.0      0.0      0.0      0.0
	// >     2.0      3.0      0.0      0.0
	// >     0.0      0.0      0.0      4.0
	// >
	printf("%s\n\n", matrix_str(m));

	matrix_set(m, 1, 2, 5.0);
	// >     0.0      0.0      0.0      0.0
	// >     2.0      3.0      5.0      0.0
	// >     0.0      0.0      0.0      4.0
	// >
	printf("%s\n\n", matrix_str(m));

	matrix_set(m, 1, 1, 0.0);
	// >     0.0      0.0      0.0      0.0
	// >     2.0      0.0      5.0      0.0
	// >     0.0      0.0      0.0      4.0
	// >
	printf("%s\n\n", matrix_str(m));

	matrix_set(m, 1, 1, 6.5);
	// >     0.0      0.0      0.0      0.0
	// >     2.0      6.5      5.0      0.0
	// >     0.0      0.0      0.0      4.0
	// >
	printf("%s\n\n", matrix_str(m));

	matrix_free(m);

	return 0;
}

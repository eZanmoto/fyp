#include <stdio.h>

#include "matrix.h"

int main() {
	matrix* m = matrix_new(3, 3);

	matrix_set(m, 1, 0, 3);

	printf("%s", matrix_str(m));

	matrix_free(m);

	return 0;
}

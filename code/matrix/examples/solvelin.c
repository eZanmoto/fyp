#include <stdio.h>

#include "err.h"
#include "matrix.h"

int main() {
	matrix* m = matrix_new(2, 2);
	matrix_set(m, 0, 0, 2.0);
	matrix_set(m, 0, 1, 3.0);
	matrix_set(m, 1, 0, 3.0);
	matrix_set(m, 1, 1, 4.0);

	matrix* b = matrix_new(2, 1);
	matrix_set(b, 0, 0, 12.0);
	matrix_set(b, 1, 0, 17.0);

	matrix* aug = matrix_aug(m, b);
	// >     2.0      3.0     12.0
	// >     3.0      4.0     17.0
	// >
	printf("%s\n\n", matrix_str(aug));
	matrix_row_reduce(aug);
	ASSERT(aug);


	// >     1.0      0.0      3.0
	// >     0.0      1.0      2.0
	printf("%s\n\n", matrix_str(aug));

	return 0;
}

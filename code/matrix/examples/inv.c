#include <stdio.h>

#include "err.h"
#include "matrix.h"

int main() {
	matrix* m = matrix_new(2, 2);
	matrix_set(m, 0, 0, 2.0);
	matrix_set(m, 0, 1, 3.0);
	matrix_set(m, 1, 0, 3.0);
	matrix_set(m, 1, 1, 4.0);

	matrix* m_ = matrix_inv(m);
	// >    -4.0      3.0
	// >     3.0     -2.0
	// >
	printf("%s\n\n", matrix_str(m_));

	matrix* id = matrix_mmul(m, m_);

	// >     1.0      0.0
	// >     0.0      1.0
	printf("%s\n", matrix_str(id));

	return 0;
}

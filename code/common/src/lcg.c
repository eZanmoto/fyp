#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "lcg.h"
#include "new.h"

struct _lcg {
	unsigned int val;
	unsigned int mod;
	unsigned int mul;
	unsigned int inc;
};

// Return the prime factors of `n`.
//
// The returned array contains the number of prime factors, `m`, in the first
// cell, followed by `m` prime factors. Any cells after this are undefined.
//
// Adapted from
// http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
unsigned int* pfactors(unsigned int n) {
	unsigned int *factors;
	NEW(factors, n);
	int m = 0;

	int i;
	for (i = 2; i <= sqrt(n); i ++) {
		while (n % i == 0) {
			factors[++m] = 2;
			n /= i;
		}
	}

	if (n > 2) {
		factors[++m] = n;
	}

	factors[0] = m;
	return factors;
}

// Generate a random LCG "multiplier" which will give a full period for a
// "modulus" of `m`.
//
// http://en.wikipedia.org/wiki/Linear_congruential_generator
// > [...] the LCG will have a full period for all seed values if and only if:
// >     [...]
// >     2. `a` - 1 is divisible by all prime factors of `m`,
// >     3. `a` - 1 is a multiple of 4 if `m` is a multiple of 4.
//
// This function generates a sufficient `a`.
int mul(int m) {
	int a = m * 0.75;
	bool sufficient = false;
	bool m_divis_4 = m % 4 == 0;
	while (!sufficient) {
		a = (a + 1) % (m - 1) + 1; // skip a == 0
		sufficient = true;

		unsigned int* factors = pfactors(m);
		int i;
		for (i = 1; sufficient && i < factors[i]; i++) {
			sufficient = (a - 1) % factors[i] == 0;
		}
		free(factors);

		sufficient = sufficient && (!m_divis_4 || (a - 1) % 4 == 0);
	}
	return a;
}

// Return the greatest common denominator of `a` and `b`.
//
// http://en.literateprograms.org/Euclidean_algorithm_(C)
int gcd(int a, int b) {
	if (b > a) goto b_larger;
	while (1) {
		a = a % b;
		if (a == 0) return b;
	b_larger:
		b = b % a;
		if (b == 0) return a;
	}
}

// Generate a random non-zero LCG "increment" which will give a period of size
// `m` for a "modulus" of `m`.
//
// http://en.wikipedia.org/wiki/Linear_congruential_generator
// > [...] the LCG will have a full period for all seed values if and only if:
// >     1. `c` and `m` are relatively prime
//
// This function generates a sufficient `c`.
int inc(int m) {
	int c = m - 1;
	while (gcd(c, m) != 1) { // note: will not exit when c == 0
		c = (c + 1) % m;
	}
	return c;
}

lcg* lcg_new(unsigned int modulus, unsigned int seed) {
	if (modulus == 0 || seed >= modulus) {
		return NULL;
	}

	lcg* lcg;
	NEW(lcg);
	lcg->mod = modulus;
	lcg->val = seed;
	lcg->mul = mul(modulus);
	lcg->inc = inc(modulus);
	return lcg;
}

unsigned int lcg_next(lcg* lcg) {
	return lcg->val = (lcg->mul * lcg->val + lcg->inc) % lcg->mod;
}

void lcg_free(lcg* lcg) {
	free(lcg);
}

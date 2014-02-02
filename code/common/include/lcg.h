/**
 * \file lcg.h
 * \brief An implementation of a linear congruential generator which guarantees
 * a full period (and by implication, uniform distribution).
 */

#ifndef _LCG_H_
#define _LCG_H_

/**
 * \brief Forward declaration of structure so members aren't exposed.
 */
struct _lcg;

/**
 * \brief A linear congruential generator.
 */
typedef struct _lcg lcg;

/**
 * \brief Return a new linear congruential generator which generates numbers in
 * the range [0, `m`), starting at `seed`.
 *
 * Returns `NULL` if `modulus` == 0 or `seed` >= `modulus`.
 */
lcg* lcg_new(unsigned int modulus, unsigned int seed);

/**
 * \brief Return the next value of `lcg`'s number sequence.
 */
unsigned int lcg_next(lcg* lcg);

/**
 * \brief Free the memory allocated to `lcg`.
 */
void lcg_free(lcg* lcg);

#endif

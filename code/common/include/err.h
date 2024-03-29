/**
 * \file err.h
 * \brief Provides error macros.
 */

#ifndef _ERR_H_
#define _ERR_H_

#include <stdio.h>
#include <stdlib.h>

/**
 * \brief Output error message (`fmt`) and quit with exit `code`.
 *
 * Output a description of where in the source code the error occurred to
 * `stderr`, followed by the error format message `fmt` to `stderr`, and return
 * from the running program with the exit `code`.
 *
 * Example usage:
 * \code FATAL(1, "expected %d bytes, got %d", n, m); \endcode
 */
#define FATAL(code, fmt, ...) \
	fprintf(stderr, "[%s:%d]" fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
	exit(code)

/**
 * \brief Exit if assertions are enabled and `cond` isn't `true`.
 *
 * Enable assertions by predefining `ENABLE_ASSERTIONS` (for example, by passing
 * `-D ENABLE_ASSERTIONS` to `gcc`).
 *
 * Example usage:
 * \code ASSERT(1 == 1); \endcode
 */
#ifdef ENABLE_ASSERTIONS
	#define ASSERT(cond) \
		if (!(cond)) { FATAL(1, "assertion failed: %s\n", #cond); }
#else
	#define ASSERT(cond)
#endif

#endif

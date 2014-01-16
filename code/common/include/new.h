/**
 * \file new.h
 * \brief Defines the `NEW` macro.
 *
 * `NEW` is used to automatically "populate" a variable, that is, to assign it
 * enough memory to contain its fields.
 *
 * Note that `NEW` only populates a single level of structures; if a structure
 * has pointers to sub-structures, these need to be populated independently.
 */

#ifndef _NEW_H_
#define _NEW_H_

#include <stdlib.h>

#include "err.h"

// A helper macro to overload `NEW`.
#define _NEW(_1, _2, NAME,...) NAME

/**
 * \brief Populate the variable `name`.
 */
#define NEW(...) _NEW(__VA_ARGS__, NEW2, NEW1)(__VA_ARGS__)

/**
 * \brief Populate the variable `name`.
 */
#define NEW1(name) NEW2(name, 1)

/**
 * \brief Populate the variable `name` as an array of size `n`.
 */
#define NEW2(name, n) \
	name = malloc((n) * sizeof *(name)); \
	if (!name) { \
		FATAL(1, "could not allocate memory"); \
	}

#endif

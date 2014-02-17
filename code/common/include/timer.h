/**
 * \file timer.h
 * \brief Provides the `timer` structure for timing intervals.
 */

#ifndef _TIMER_H_
#define _TIMER_H_

// Forward declaration of structure so members aren't exposed.
struct _timer;

/**
 * \brief Provides the utility to time intervals.
 */
typedef struct _timer timer;

/**
 * \brief Return a new timer.
 */
timer* timer_new();

/**
 * \brief Start `t` timing (cf. `timer_elapsed()`).
 */
void timer_start(timer* t);

/**
 * \brief Return the nanoseconds elapsed since the last time `timer_start()` was
 * called on `t`.
 */
unsigned long timer_nsec(timer* t);

#endif

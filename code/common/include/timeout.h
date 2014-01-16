/**
 * \file timeout.h
 * \brief 
 */

#ifndef _TIMEOUT_H_
#define _TIMEOUT_H_

/**
 * \brief Call `timeout_func` after `milliseconds` have elapsed.
 */
void set_timeout(unsigned int milliseconds, void (*timeout_func)());

/**
 * \brief Cancel the last timeout function that was set to occur.
 */
void clear_timeout();

#endif

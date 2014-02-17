// Most of this code was adapted from https://gist.github.com/jbenet/1087739.

#include <math.h>
#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

#include "new.h"
#include "timer.h"

#define NSEC_PER_SEC 1000000000

struct _timer {
	struct timespec start;
};

timer* timer_new() {
	timer* t;
	NEW(t);
	return t;
}

void get_time(struct timespec* ts) {
#ifdef __MACH__ // OS X does not have `clock_gettime`, use `clock_get_time`.
	clock_serv_t cclock;
	struct mach_timespec mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts->tv_sec = mts.tv_sec;
	ts->tv_nsec = mts.tv_nsec;
#else
	clock_gettime(CLOCK_REALTIME, ts);
#endif
}

void timer_start(timer* t) {
	get_time(&(t->start));
}

unsigned long timer_nsec(timer* t) {
	// Ideally this function would signal an error if `timer_start()` wasn't
	// called before `timer_nsec()` - this won't be currently implemented for
	// the sake of simplicity, but will hopefully be implemented soon.
	struct timespec end;
	get_time(&end);
	return (end.tv_sec - t->start.tv_sec) * NSEC_PER_SEC +
		(end.tv_nsec - t->start.tv_nsec);
}

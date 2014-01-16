#include <errno.h>
#include <signal.h>
#include <sys/time.h>

#include "err.h"
#include "timeout.h"

// `setitimer()` doesn't allow the `tv_usec` fields of its arguments to be
// greater than this value.
#define MAX_MICROSECS 1000000

struct timeval timeval_new(unsigned int microseconds) {
	struct timeval tv;
	tv.tv_sec  = microseconds / MAX_MICROSECS;
	tv.tv_usec = microseconds % MAX_MICROSECS;
	return tv;
}

void set_time(unsigned int milliseconds) {
	struct itimerval new;
	new.it_value    = timeval_new(milliseconds * 1000);
	new.it_interval = timeval_new(0);
	if (setitimer(ITIMER_REAL, &new, NULL) == EINVAL) {
		// Shouldn't happen, but just in case.
		FATAL(2, "%d should not be greater than %d",
				new.it_value.tv_usec, MAX_MICROSECS);
	}
}

void set_timeout(unsigned int milliseconds, void (*timeout_func)()) {
	signal(SIGALRM, timeout_func);
	set_time(milliseconds);
}

void clear_timeout() {
	set_time(0);
}

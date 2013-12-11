#!/usr/bin/python

# Finds the minimum MAX_SIZE, 2^n, for which all implementations take
# negligible time to execute a function `f`.

import commands
import random
import string

from matplotlib import pyplot

impls = ['array', 'linked']

min_ = None
for impl in impls:
    max_size = int(commands.getoutput("build/%s_max_size" % impl))
    if min_ is None or max_size < min_:
        min_ = max_size

random.seed(0x00ffff)
for impl in impls:
    # ys = None
    # for i in xrange(1, 10):
    code, output = commands.getstatusoutput("build/%s_time_per_func %s" % (impl, min_))
    if code != 0:
        print output
        break
    ys = map(float, string.split(output))[1:]
    # ys = ys_ if ys is None else [ (a+b) / 2 for (a, b) in zip(ys, ys_) ]
    # FIXME why not equivalent to xs = range(0, min_, min_ / len(ys))
    xs = [x * (min_ / len(ys)) for x in xrange(0, len(ys))]
    pyplot.plot(xs, ys, '#%06x' % random.randint(0, 0xffffff), label=impl)

pyplot.title("Timing for <construct>")
pyplot.xlabel("Matrix size")
pyplot.ylabel("Time")
pyplot.legend(loc='upper left')
pyplot.show()

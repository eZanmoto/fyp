#!/bin/sh

# Outputs a number of graphs to the `build/fig` directory which have been deemed
# to be representative of the information obtained by this project.

if [ $# -lt 1 ] ; then
	echo "Usage: $0 <cc-1> {cc-i}"
	exit 1
fi

for CC in $* ; do
	bin/plot.py -f smul,mmul,mmul_s,row_reduce_s -s 100 -n 10 -c $CC

	for IMPL in smul mmul mmul_s row_reduce_s ; do
		bin/plot.py -f $IMPL -s 100 -n 10 -c $CC -o 0,1,2
	done
done

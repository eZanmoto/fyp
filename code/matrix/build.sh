#!/bin/sh

# Outputs a number of graphs to the `build/fig` directory which have been deemed
# to be representative of the information obtained by this project.

function run {
	CMD=$*
	echo $CMD
	OUTPUT=`$CMD 2>&1`
	if [ $? -ne 0 ] ; then
		echo "$OUTPUT"
		exit 1
	fi
}

if [ $# -lt 1 ] ; then
	echo "Usage: $0 <cc-1> {cc-i}"
	exit 1
fi

for CC in $* ; do
	run bin/plot.py -f smul,mmul,mmul_s,row_reduce_s -s 100 -n 10 -c $CC

	for IMPL in smul mmul mmul_s row_reduce_s ; do
		run bin/plot.py -f $IMPL -s 100 -n 10 -c $CC -o 0,1,2
	done
done

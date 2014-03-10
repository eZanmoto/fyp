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

mkdir -p build/fig

for CC in $* ; do
	for OPT in 0 1 2 3 ; do
		run bin/timer.py -f smul,mmul,mmul_s,row_reduce_s -c $CC -o $OPT
    TGT=time_smul,mmul,mmul_s,row_reduce_s_${CC}_${OPT}_100
    run bin/plot.py build/dat/$TGT.json build/fig/$TGT.jpg
	done

	for IMPL in smul mmul mmul_s row_reduce_s ; do
		run bin/timer.py -f $IMPL -c $CC -o 0,1,2
    TGT=time_${IMPL}_${CC}_0,1,2_100
    run bin/plot.py build/dat/$TGT.json build/fig/$TGT.jpg
	done
done

#!/bin/bash

# Simple test script for testing that the output of an example is as expected.
# Expected output is specified line-by-line in the source file of the example.
#
# Usage: bin/check_egs.sh <source> <binary> [lib_path]
#
# <source> is the example C source file for <binary>
# <binary> is the binary whose output is to be tested
# [lib_path] is an optional library path

EXP=`grep '// >' $1 | sed 's/^[^>]*>//'`

export DYLD_LIBRARY_PATH=$3:$DYLD_LIBRARY_PATH
export LD_LIBRARY_PATH=$3:$LD_LIBRARY_PATH
ACT=`$2`

if [ "$EXP" != "$ACT" ] ; then
	echo Expected:
	echo "$EXP"
	echo Got:
	echo "$ACT"
	exit 1
fi

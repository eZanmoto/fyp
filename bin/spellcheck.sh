#!/bin/bash

# Copyright 2013 Sean Kelleher. All rights reserved.
# Use of this source code is governed by a GPL
# license that can be found in the LICENSE file.

# A wrapper for the `aspell` command.

if [ $# -ne 1 ] ; then
	echo "usage: $0 <file.tex>"
	exit 1
fi

if [ ! -f $1 ] ; then
	echo "'$1' does not exist"
	exit 2
fi

MISSPELLS=`cat $1 | aspell -l en_IE -t --home-dir=$PWD list | uniq`
if [ "$MISSPELLS" != "" ] ; then
	echo "Please correct the following misspellings:"
	for MISSPELL in $MISSPELLS ; do
		echo $MISSPELL
		grep -H -n $MISSPELL $1 > /dev/stderr
	done
	exit 2
fi

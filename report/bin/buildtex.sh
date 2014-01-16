#!/bin/bash

# Copyright 2013 Sean Kelleher. All rights reserved.
# Use of this source code is governed by a GPL
# license that can be found in the LICENSE file.

# Build a LaTeX file to a directory.

if [ $# -ne 2 ] ; then
	echo "usage: $0 <file-root> <output-dir>"
	exit 1
fi

# This script changes the working directory for the execution of the `pdflatex`
# command so that the output, and all auxiliary files, will be saved to the
# build directory. This is done because different implementations of `pdflatex`
# tend to have different ways of changing the destination directory, and we want
# implementation-independence.
cd $2

pdflatex -interaction=nonstopmode $1.tex > /dev/null
if [ -f ../$1.bib ] ; then
	ln -s ../$1.bib
	bibtex $1
	pdflatex -interaction=nonstopmode $1.tex > /dev/null
fi
# We run `pdflatex` a second/third time to solve cross-referencing issues, such
# as a label being defined after a reference to it.
pdflatex -interaction=nonstopmode $1.tex

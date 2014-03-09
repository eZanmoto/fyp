README
======

Sean Kelleher
-------------

### About

This project contains code for benchmarking the functions of various matrix
implementations.

### Deliverables

The primary "output" of this project is a collection of graphs plotting the
various benchmarks obtained from the matrix implementations. To create these
graphs, run (from the root directory of the project):

    ./build.sh gcc

`gcc` can be replaced by any positive number of C compilers. Note that currently
all C compilers must be able to process some of the same flags as `gcc`, such as
flags to do with enabling errors and optimization levels. The script outputs a
number of images to `build/fig` which have been determined to be representative
of all the relevant information obtained from this project.

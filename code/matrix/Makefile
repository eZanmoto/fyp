IMPLS=linked array

CC=gcc
CFLAGS=-Wall -Werror

BINDIR=bin
SRCDIR=src
TGTDIR=build

.PHONY: all
all: clean build-all

.PHONY: run
run: clean build-lib
	$(BINDIR)/plot.py

.PHONY: build-all
build-all: build-lib build-doc

.PHONY: build-lib
build-lib: \
	$(TGTDIR) \
	$(patsubst %, $(TGTDIR)/%_max_size, $(IMPLS)) \
	$(patsubst %, $(TGTDIR)/%_time_per_func, $(IMPLS))

.PHONY: build-doc
build-doc:
	doxygen

.PHONY: main
main: clean $(TGTDIR) $(TGTDIR)/main

$(TGTDIR)/main: main.c $(SRCDIR)/matrix.c $(SRCDIR)/matrix_array.c
	$(CC) $(CFLAGS) -I include $^ -g -o $@

$(TGTDIR)/%_max_size: $(SRCDIR)/max_size.c $(SRCDIR)/matrix.c $(SRCDIR)/matrix_%.c
	$(CC) $(CFLAGS) -I include $^ -g -o $@

$(TGTDIR)/%_time_per_func: $(SRCDIR)/time_per_func.c $(SRCDIR)/matrix.c $(SRCDIR)/matrix_%.c
	$(CC) $(CFLAGS) -I include $^ -g -o $@

$(TGTDIR):
	mkdir $(TGTDIR)

.PHONY: clean
clean:
	rm -rf $(TGTDIR)

# Targets
#
# all:          Run all builds
# rebuild:      Make a clean build
# build-all:    Build all deliverables
# build-bin:    Build core binaries
# build-dat:    Build data files
# build-doc:    Build documentation
# build-egs:    Build example binaries
# check:        Run all tests
# check-egs:    Tests example code
# clean:        Removes the local build files

# Dependency project directories
COMMON:=../common

# Directories
EGSDIR:=examples
SRCDIR:=src

TGTDIR:=build

TGTBIN:=$(TGTDIR)/bin
TGTDAT:=$(TGTDIR)/dat
TGTDOC:=$(TGTDIR)/doc
TGTEGS:=$(TGTDIR)/examples

INCDIRS:=include $(COMMON)/include
LIBDIRS:=$(COMMON)/build

# Files
TARGETS:=$(patsubst $(SRCDIR)/%.c,%,$(wildcard $(SRCDIR)/time_*.c))
INCLUDES:=$(foreach INCDIR,$(INCDIRS),$(wildcard $(INCDIR)/*))
EXAMPLES:=$(patsubst $(EGSDIR)/%.c,%,$(wildcard $(EGSDIR)/*))

IMPLS:=$(patsubst $(SRCDIR)/matrix_%.c,%,$(wildcard $(SRCDIR)/matrix_*.c))
ifndef IMPL
IMPL:=$(word 1,$(IMPLS))
endif
ifeq ($(wildcard $(SRCDIR)/matrix_$(IMPL).c),)
$(error '$(IMPL)' is not a known matrix implementation ($(IMPLS)))
endif

# Compiler options
ifndef CC
CC:=cc
endif
ifndef OPT
OPT:=0
endif
CFLAGS:=-Wall -Wextra -Wconversion -Werror -g -O$(OPT)
CINCS:=$(addprefix -I,$(INCDIRS))
CLIBS:=$(addprefix -L,$(LIBDIRS)) $(addprefix -l,common)

# A signature that's appended to names of binaries to differentiate them
SIG:=$(IMPL)_$(CC)_$(OPT)

# Timing parameters
ifndef SIZE
SIZE:=100
endif
ifndef NUM_POINTS
NUM_POINTS:=10
endif

# Variables for platform independence
ifeq ($(shell uname -s),Darwin)
LIB_PATH:=DYLD_LIBRARY_PATH
else
LIB_PATH:=LD_LIBRARY_PATH
endif

.PHONY: all
all: build-all

.PHONY: rebuild
rebuild: clean build-all

.PHONY: build-all
build-all: build-bin build-dat build-doc build-egs

.PHONY: build-dat
build-dat: $(patsubst %,$(TGTDAT)/%_$(SIG)_$(SIZE)_$(NUM_POINTS).txt,$(TARGETS))

# This recipe writes to a temporary file first so that the file generated from
# an erroneous execution won't be regarded as a built target.
$(TGTDAT)/%_$(SIZE)_$(NUM_POINTS).txt: $(TGTBIN)/% $(TGTBIN)/libcommon.so | $(TGTDAT)
	$(LIB_PATH)=$(TGTBIN):$$$(LIB_PATH) $< $(SIZE) $(NUM_POINTS) > $@~
	mv $@~ $@

$(TGTDIR)/%/libcommon.so: $(COMMON)/build/libcommon.so | $(TGTDIR)/%
	ln -s ../../$< $@

$(TGTBIN) $(TGTDAT) $(TGTDOC) $(TGTEGS): | $(TGTDIR)
	mkdir $@

$(TGTDIR):
	mkdir $@

.PHONY: build-bin
build-bin: $(patsubst %,$(TGTBIN)/%_$(SIG),$(TARGETS)) $(TGTBIN)/libcommon.so

$(TGTBIN)/%_$(SIG): $(SRCDIR)/%.c $(SRCDIR)/matrix.c $(SRCDIR)/matrix_$(IMPL).c | $(TGTBIN)
	$(CC) $(CFLAGS) $(CLIBS) $(CINCS) $^ -o $@

.PHONY: build-doc
build-doc: | $(TGTDOC)/html

$(TGTDOC)/html: $(SRCDIR) $(INCDIR) Doxyfile | $(TGTDOC)
	doxygen > $(TGTDOC)/doxygen.log

.PHONY: build-egs
build-egs: $(patsubst %,$(TGTEGS)/%_$(SIG),$(EXAMPLES)) $(TGTEGS)/libcommon.so

$(TGTEGS)/%_$(SIG): $(EGSDIR)/%.c $(SRCDIR)/matrix.c $(SRCDIR)/matrix_$(IMPL).c | $(TGTEGS)
	$(CC) $(CFLAGS) $(CLIBS) $(CINCS) -D ENABLE_ASSERTIONS $^ -o $@

.PHONY: check
check:
	for IMPL in $(IMPLS) ; do \
		IMPL=$$IMPL make check-egs ; \
		if [ $$? -ne 0 ] ; then \
			exit 2 ; \
		fi ; \
	done

.PHONY: check-egs
check-egs: $(addprefix check-,$(EXAMPLES))

check-%: $(EGSDIR)/%.c $(TGTEGS)/%_$(SIG) $(TGTEGS)/libcommon.so
	bin/check_eg.sh $(wordlist 1,2,$^) $(TGTEGS)

.PHONY: clean
clean:
	rm -rf $(TGTDIR)

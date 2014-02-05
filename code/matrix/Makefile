# Targets
#
# all:          Run all builds
# rebuild:      Make a clean build
# build-all:    Build all deliverables
# build-bin:    Build core binaries
# build-dat:    Build data files
# build-doc:    Build documentation
# build-egs:    Build example binaries
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
TGTOBJ:=$(TGTDIR)/objects

INCDIRS:=include $(COMMON)/include
LIBDIRS:=$(COMMON)/build

# Files
TARGETS:=$(patsubst $(SRCDIR)/%.c,%,$(wildcard $(SRCDIR)/time_*.c))
OBJECTS:=$(patsubst $(SRCDIR)/%.c,$(TGTDIR)/%.o,$(wildcard $(SRCDIR)/*))
INCLUDES:=$(foreach INCDIR,$(INCDIRS),$(wildcard $(INCDIR)/*))
EXAMPLES:=$(patsubst $(EGSDIR)/%.c,%,$(wildcard $(EGSDIR)/*))

ifndef IMPL
IMPL:=1darray
endif

IMPLS:=$(patsubst $(SRCDIR)/matrix_%.c,%,$(wildcard $(SRCDIR)/matrix_*.c))
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
CFLAGS:=-Wall -Werror -g -O$(OPT)
CINCS:=$(addprefix -I,$(INCDIRS))
CLIBS:=$(addprefix -L,$(LIBDIRS)) $(addprefix -l,common)

# A signature that's appended to names of binaries to differentiate them
SIG:=$(IMPL)_$(CC)_$(OPT)

# Timing parameters
ifndef SIZE
SIZE:=512
endif
ifndef NUM_POINTS
NUM_POINTS:=1000
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
	cd $(TGTBIN) && ./$(notdir $<) $(SIZE) $(NUM_POINTS) > ../../$@~
	mv $@~ $@

$(TGTBIN)/libcommon.so $(TGTEGS)/libcommon.so: $(COMMON)/build/libcommon.so
	ln -s ../../$< $@

$(TGTBIN) $(TGTDAT) $(TGTDOC) $(TGTEGS) $(TGTOBJ): | $(TGTDIR)
	mkdir $@

$(TGTDIR):
	mkdir $@

.PHONY: build-bin
build-bin: $(patsubst %,$(TGTBIN)/%_$(SIG),$(TARGETS))

$(TGTBIN)/%_$(SIG): $(TGTOBJ)/%.o $(TGTOBJ)/matrix.o $(TGTOBJ)/matrix_$(IMPL).o | $(TGTBIN)
	$(CC) $(CFLAGS) $(CLIBS) $^ -o $@

$(TGTOBJ)/%.o: $(SRCDIR)/%.c $(INCLUDES) | $(TGTOBJ)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@

.PHONY: build-doc
build-doc: | $(TGTDOC)/html

$(TGTDOC)/html: $(SRCDIR) $(INCDIR) Doxyfile | $(TGTDOC)
	doxygen > $(TGTDOC)/doxygen.log

.PHONY: build-egs
build-egs: $(patsubst %,$(TGTEGS)/%_$(SIG),$(EXAMPLES)) $(TGTEGS)/libcommon.so

$(TGTEGS)/%_$(SIG): $(TGTOBJ)/%.o $(TGTOBJ)/matrix.o $(TGTOBJ)/matrix_$(IMPL).o
	$(CC) $(CFLAGS) $(CLIBS) $^ -o $@

$(TGTOBJ)/%.o: $(EGSDIR)/%.c $(INCLUDES) $(TGTOBJ) | $(TGTEGS)
	$(CC) $(CFLAGS) $(CINCS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(TGTDIR)

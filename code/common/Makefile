# Targets
#
# all:          Run all builds
# rebuild:      Make a clean build
# build-all:    Build all deliverables
# build-lib:    Build the libcommon library
# build-doc:    Build documentation
# clean:        Removes the local build files

# SONAME is the linker option which specifies the name of the shared object, but
# has a different name under GNU/Linux and Mac OS X.
ifeq ($(shell uname),Darwin)
	SONAME=-install_name
else
	SONAME=-soname
endif

# Directories
SRCDIR:=src

TGTDIR:=build

TGTDOC:=$(TGTDIR)/doc

INCDIRS:=include

# Files
INCLUDES:=$(foreach INCDIR,$(INCDIRS),$(wildcard $(INCDIR)/*))
OBJECTS:=$(patsubst $(SRCDIR)/%.c,$(TGTDIR)/%.o,$(wildcard $(SRCDIR)/*))
TARGET:=libcommon.so

# Compiler options
ifndef CC
CC:=gcc
endif
CFLAGS:=-Wall -Werror -g
CINCS:=$(addprefix -I,$(INCDIRS))

.PHONY: all
all: build-all

.PHONY: all
rebuild: clean build-all

.PHONY: build-all
build-all: build-lib build-doc

.PHONY: build-lib
build-lib: $(TGTDIR)/$(TARGET)

$(TGTDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -shared -Wl,$(SONAME),$(TARGET) $^ -o $@

$(TGTDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES) | $(TGTDIR)
	$(CC) $(CFLAGS) $(CINCS) -fPIC -c $< -o $@

$(TGTDIR):
	mkdir $@

.PHONY: build-doc
build-doc: | $(TGTDOC)/html

$(TGTDOC)/html: $(SRCDIR) | $(TGTDOC)
	doxygen > $(TGTDOC)/doxygen.log

$(TGTDOC): | $(TGTDIR)
	mkdir $@

.PHONY: clean
clean:
	rm -rf $(TGTDIR)

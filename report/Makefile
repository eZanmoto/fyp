# Copyright 2013 Sean Kelleher. All rights reserved.
# Use of this source code is governed by a GPL
# license that can be found in the LICENSE file.
#
# Targets
#
# rebuild:      Make a clean build
# build-all:    Build all deliverables
# check:        Run tests
# clean:        Removes the local build files

# Directories
BINDIR:=bin
TGTDIR:=build

# Files
SOURCES:=$(patsubst %.tex,%,$(wildcard *.tex))

.PHONY: rebuild
rebuild: clean build-all

.PHONY: build-all
build-all: check $(patsubst %,$(TGTDIR)/%.pdf,$(SOURCES))

$(TGTDIR)/%.pdf: $(TGTDIR)/%.tex
	$(BINDIR)/buildtex.sh $(basename $(notdir $<)) $(TGTDIR)

# "Copy" local files to the build directory if they're required there.
$(TGTDIR)/%: % $(TGTDIR)
	ln -s ../$< $(TGTDIR)

$(TGTDIR):
	mkdir $(TGTDIR)

.PHONY: check
check: clean $(addprefix check-,$(SOURCES))

check-%: %.tex
	$(BINDIR)/spellcheck.sh $<

.PHONY: clean
clean:
	rm -rf $(TGTDIR)

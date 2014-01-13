# Copyright 2013 Sean Kelleher. All rights reserved.
# Use of this source code is governed by a GPL
# license that can be found in the LICENSE file.

# Directories
BINDIR=bin
TGTDIR=build

.PHONY: all
all: check $(TGTDIR)/paper.pdf $(TGTDIR)/report.pdf

$(TGTDIR)/%.pdf: $(TGTDIR)/%.tex $(TGTDIR)
	$(BINDIR)/buildtex.sh $(basename $(notdir $<)) $(TGTDIR)

.PHONY: check
check: clean check-paper check-report

check-%: %.tex
	$(BINDIR)/spellcheck.sh $<

# "Copy" local files to the build directory if they're required there.
$(TGTDIR)/%: % $(TGTDIR)
	ln -s ../$< $(TGTDIR)

$(TGTDIR):
	mkdir $(TGTDIR)

.PHONY: clean
clean:
	rm -rf $(TGTDIR)

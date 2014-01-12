# Copyright 2013 Sean Kelleher. All rights reserved.
# Use of this source code is governed by a GPL
# license that can be found in the LICENSE file.

# Directories
BINDIR=bin
OUTDIR=build

.PHONY: all
all: check $(OUTDIR)/paper.pdf $(OUTDIR)/report.pdf
#
$(OUTDIR)/%.pdf: $(OUTDIR)/%.tex $(OUTDIR)
	$(BINDIR)/buildtex.sh $(basename $(notdir $<)) $(OUTDIR)

.PHONY: check
check: clean check-paper check-report

check-%: %.tex
	$(BINDIR)/spellcheck.sh $<

# "Copy" local files to the build directory if they're required there.
$(OUTDIR)/%: % $(OUTDIR)
	ln -s ../$< $(OUTDIR)

$(OUTDIR):
	mkdir $(OUTDIR)

.PHONY: clean
clean:
	rm -rf $(OUTDIR)

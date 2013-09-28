# Copyright 2013 Sean Kelleher. All rights reserved.
# Use of this source code is governed by a GPL
# license that can be found in the LICENSE file.

# Directories
OUTDIR=build

.PHONY: all
all: $(OUTDIR)/paper.pdf

# This recipe changes the working directory for the execution for the `pdflatex`
# command so that the output, and all auxiliary files, will be saved to the
# build directory. This is done because different implementations of `pdflatex`
# tend to have different ways of changing the destination directory, and we want
# implementation-independence.
$(OUTDIR)/paper.pdf: paper.tex $(OUTDIR)
	cd $(OUTDIR) ; \
		ln -s ../$< ; \
		pdflatex $<

$(OUTDIR):
	mkdir $(OUTDIR)

.PHONY: clean
clean:
	rm -rf $(OUTDIR)

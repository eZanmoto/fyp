# Copyright 2013 Sean Kelleher. All rights reserved.
# Use of this source code is governed by a GPL
# license that can be found in the LICENSE file.

# Directories
OUTDIR=build

.PHONY: all
all: clean $(OUTDIR)/paper.pdf

# This recipe changes the working directory for the execution of the `pdflatex`
# command so that the output, and all auxiliary files, will be saved to the
# build directory. This is done because different implementations of `pdflatex`
# tend to have different ways of changing the destination directory, and we want
# implementation-independence.
$(OUTDIR)/%.pdf: $(OUTDIR)/%.tex $(OUTDIR)/%_refs.bib $(OUTDIR)
	$(eval TARGET=$(notdir $<))
	cd $(OUTDIR) ; \
		pdflatex $(TARGET) ; \
		pdflatex $(TARGET)

# "Copy" local files to the build directory if they're required there.
$(OUTDIR)/%: % $(OUTDIR)
	ln -s ../$< $(OUTDIR)

$(OUTDIR):
	mkdir $(OUTDIR)

.PHONY: clean
clean:
	rm -rf $(OUTDIR)

# Copyright 2013 Sean Kelleher. All rights reserved.
# Use of this source code is governed by a GPL
# license that can be found in the LICENSE file.

# Directories
OUTDIR=build

.PHONY: all
all: check $(OUTDIR)/paper.pdf $(OUTDIR)/report.pdf

# This recipe changes the working directory for the execution of the `pdflatex`
# command so that the output, and all auxiliary files, will be saved to the
# build directory. This is done because different implementations of `pdflatex`
# tend to have different ways of changing the destination directory, and we want
# implementation-independence.
#
# We run `pdflatex` twice to solve cross-referencing issues, such as a label
# occurring after a reference to it.
$(OUTDIR)/%.pdf: $(OUTDIR)/%.tex $(OUTDIR)/%_refs.bib $(OUTDIR)
	$(eval TARGET=$(notdir $<))
	cd $(OUTDIR) ; \
		pdflatex -interaction=nonstopmode $(TARGET) && \
		bibtex $(basename $(TARGET)) && \
		pdflatex -interaction=nonstopmode $(TARGET) && \
		pdflatex -interaction=nonstopmode $(TARGET)

.PHONY: check
check: clean check-paper check-report

check-%: %.tex
	@MISSPELLS=`cat $< | aspell -l en_IE -t --home-dir=$(CURDIR) list | uniq` ; \
	if [ "$$MISSPELLS" != "" ] ; then \
		echo "Please correct the following misspellings:" ; \
		for MISSPELL in $$MISSPELLS ; do \
			echo $$MISSPELL ; \
			grep -H -n $$MISSPELL $< > /dev/stderr ; \
		done ; \
		exit 2 ; \
	fi

# "Copy" local files to the build directory if they're required there.
$(OUTDIR)/%: % $(OUTDIR)
	ln -s ../$< $(OUTDIR)

$(OUTDIR):
	mkdir $(OUTDIR)

.PHONY: clean
clean:
	rm -rf $(OUTDIR)

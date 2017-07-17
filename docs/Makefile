# Minimal makefile for Sphinx documentation

# You can set these variables from the command line.
SPHINXOPTS    =
SPHINXBUILD   = python -msphinx
SPHINXPROJ    = Pessum 
SOURCEDIR     = source
BUILDDIR      = build
GH_PAGES_SOURCES = $(SOURCEDIR) Makefile

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

# Create Github pages
gh-pages:
	git checkout gh-pages
	rm -rf build sources _static
	git checkout master $(GH_PAGES_SOURCES)
	git reset HEAD
	make latex
	make latex
	make html
	mv -fv build/html/* ./
	git add -A
	git commit -m"Generated gh-pages for `git log master -1 --pretty=short --abbrev-commit`" && git push origin gh-pages; git checkout master


.PHONY: help Makefile gh-pages

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

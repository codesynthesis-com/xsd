# file      : doc/cxx/tree/guide/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../build/bootstrap.make

default  := $(out_base)/
install  := $(out_base)/.install
dist     := $(out_base)/.dist
dist-win := $(out_base)/.dist-win
clean    := $(out_base)/.clean

# Build.
#
$(default): $(out_base)/cxx-tree-guide.ps $(out_base)/cxx-tree-guide.pdf


$(out_base)/cxx-tree-guide.ps: $(src_base)/index.xhtml   \
                               $(src_base)/guide.html2ps \
                               | $(out_base)/.
	$(call message,html2ps $<,html2ps -f $(src_base)/guide.html2ps -o $@ $<)

$(out_base)/cxx-tree-guide.pdf: $(out_base)/cxx-tree-guide.ps | $(out_base)/.
	$(call message,ps2pdf $<,ps2pdf14 $< $@)

# Install & Dist.
#
$(install): path := $(subst $(src_root)/doc/,,$(src_base))
$(dist): path := $(subst $(src_root)/,,$(src_base))

$(install): $(out_base)/cxx-tree-guide.ps $(out_base)/cxx-tree-guide.pdf
	$(call install-data,$(src_base)/index.xhtml,$(install_doc_dir)/xsd/$(path)/index.xhtml)
	$(call install-data,$(out_base)/cxx-tree-guide.ps,$(install_doc_dir)/xsd/$(path)/cxx-tree-guide.ps)
	$(call install-data,$(out_base)/cxx-tree-guide.pdf,$(install_doc_dir)/xsd/$(path)/cxx-tree-guide.pdf)

$(dist): $(out_base)/cxx-tree-guide.ps $(out_base)/cxx-tree-guide.pdf
	$(call install-data,$(src_base)/index.xhtml,$(dist_prefix)/$(path)/index.xhtml)
	$(call install-data,$(out_base)/cxx-tree-guide.ps,$(dist_prefix)/$(path)/cxx-tree-guide.ps)
	$(call install-data,$(out_base)/cxx-tree-guide.pdf,$(dist_prefix)/$(path)/cxx-tree-guide.pdf)

$(dist-win): $(dist)


# Clean
#
$(clean):
ifneq ($(xsd_clean_gen),n)
	$(call message,rm $$1,rm -f $$1,$(out_base)/cxx-tree-guide.ps)
	$(call message,rm $$1,rm -f $$1,$(out_base)/cxx-tree-guide.pdf)
endif

# How to.
#
$(call include,$(bld_root)/install.make)

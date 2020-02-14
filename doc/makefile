# file      : doc/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../build/bootstrap.make

default  := $(out_base)/
install  := $(out_base)/.install
dist     := $(out_base)/.dist
dist-win := $(out_base)/.dist-win
clean    := $(out_base)/.clean

# Import.
#
$(call import,\
  $(scf_root)/import/cli/stub.make,\
  cli: cli,cli-rules: cli_rules)

# Build.
#
$(default):           \
$(out_base)/cxx/      \
$(out_base)/xsd.xhtml \
$(out_base)/xsd.1

# Man/html pages.
#
$(out_base)/xsd.xhtml $(out_base)/xsd.1: cli := $(cli)
$(out_base)/xsd.xhtml $(out_base)/xsd.1: cli_options += -I $(src_root)/xsd

$(out_base)/xsd.xhtml $(out_base)/xsd.1: \
$(src_root)/xsd/options.cli              \
$(src_root)/xsd/cxx/options.cli          \
$(src_root)/xsd/cxx/tree/options.cli     \
$(src_root)/xsd/cxx/parser/options.cli

# Assemble the options from different files in a specific order.
#

# XHTML
#
$(out_base)/xsd.xhtml: $(src_base)/xsd-prologue.xhtml      \
                       $(src_base)/xsd-epilogue.xhtml      \
                       $(src_base)/xsd-tree-header.xhtml   \
                       $(src_base)/xsd-parser-header.xhtml \
                       | $(out_base)/.
# Common options.
#
	$(call message,cli-html $$1,$(cli) $(cli_options) --generate-html \
--stdout --suppress-undocumented --exclude-base --class CXX::options \
--class options --html-prologue-file $(src_base)/xsd-prologue.xhtml \
$$1 >$@, $(src_root)/xsd/cxx/options.cli)

# C++/Tree options.
#
	$(call message,cli-html $$1,$(cli) $(cli_options) --generate-html \
--stdout --suppress-undocumented --exclude-base \
--html-prologue-file $(src_base)/xsd-tree-header.xhtml \
$$1 >>$@, $(src_root)/xsd/cxx/tree/options.cli)

# C++/Parser options.
#
	$(call message,cli-html $$1,$(cli) $(cli_options) --generate-html \
--stdout --suppress-undocumented --exclude-base \
--html-prologue-file $(src_base)/xsd-parser-header.xhtml \
--html-epilogue-file $(src_base)/xsd-epilogue.xhtml \
$$1 >>$@, $(src_root)/xsd/cxx/parser/options.cli)

# MAN
#
$(out_base)/xsd.1: $(src_base)/xsd-prologue.1      \
                   $(src_base)/xsd-epilogue.1      \
                   $(src_base)/xsd-tree-header.1   \
                   $(src_base)/xsd-parser-header.1 \
                   | $(out_base)/.
# Common options.
#
	$(call message,cli-man $$1,$(cli) $(cli_options) --generate-man \
--stdout --suppress-undocumented --exclude-base --class CXX::options \
--class options --man-prologue-file $(src_base)/xsd-prologue.1 \
$$1 >$@, $(src_root)/xsd/cxx/options.cli)

# C++/Tree options.
#
	$(call message,cli-man $$1,$(cli) $(cli_options) --generate-man \
--stdout --suppress-undocumented --exclude-base \
--man-prologue-file $(src_base)/xsd-tree-header.1 \
$$1 >>$@, $(src_root)/xsd/cxx/tree/options.cli)

# C++/Parser options.
#
	$(call message,cli-man $$1,$(cli) $(cli_options) --generate-man \
--stdout --suppress-undocumented --exclude-base \
--man-prologue-file $(src_base)/xsd-parser-header.1 \
--man-epilogue-file $(src_base)/xsd-epilogue.1 \
$$1 >>$@, $(src_root)/xsd/cxx/parser/options.cli)


# Install.
#
$(install): $(out_base)/cxx/.install \
            $(out_base)/xsd.xhtml    \
            $(out_base)/xsd.1	
	$(call install-data,$(src_base)/default.css,$(install_doc_dir)/xsd/default.css)
	$(call install-data,$(out_base)/xsd.xhtml,$(install_doc_dir)/xsd/xsd.xhtml)
	$(call install-data,$(src_base)/custom-literals.xsd,$(install_doc_dir)/xsd/custom-literals.xsd)
	$(call install-data,$(out_base)/xsd.1,$(install_man_dir)/man1/xsd.1)

# Dist.
#
dist-common := $(out_base)/.dist-common

$(dist-common): $(out_base)/xsd.xhtml \
                $(out_base)/xsd.1
	$(call install-data,$(src_base)/default.css,$(dist_prefix)/doc/default.css)
	$(call install-data,$(out_base)/xsd.xhtml,$(dist_prefix)/doc/xsd.xhtml)
	$(call install-data,$(out_base)/xsd.1,$(dist_prefix)/doc/xsd.1)
	$(call install-data,$(src_base)/custom-literals.xsd,$(dist_prefix)/doc/custom-literals.xsd)

$(dist): $(dist-common) $(out_base)/cxx/.dist
$(dist-win): $(dist-common) $(out_base)/cxx/.dist-win

# Clean.
#
$(clean): $(out_base)/cxx/.clean
ifneq ($(xsd_clean_gen),n)
	$(call message,rm $$1,rm -f $$1,$(out_base)/xsd.1)
	$(call message,rm $$1,rm -f $$1,$(out_base)/xsd.xhtml)
endif

# Generated .gitignore.
#
ifeq ($(out_base),$(src_base))
$(out_base)/xsd.xhtml $(out_base)/xsd.1: | $(out_base)/.gitignore

$(out_base)/.gitignore: files := xsd.1 xsd.xhtml
$(clean): $(out_base)/.gitignore.clean

$(call include,$(bld_root)/git/gitignore.make)
endif

$(call include,$(bld_root)/install.make)
$(call import,$(src_base)/cxx/makefile)

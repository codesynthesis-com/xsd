# file      : makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))build/bootstrap.make

default  := $(out_base)/
test     := $(out_base)/.test
install  := $(out_base)/.install
dist     := $(out_base)/.dist
dist-win := $(out_base)/.dist-win
dist-pre := $(out_base)/.dist-pre
clean    := $(out_base)/.clean

.PHONY: $(dist-pre)

$(default): $(out_base)/xsd/      \
            $(out_base)/tests/    \
            $(out_base)/examples/ \
            $(out_base)/doc/

# Test.
#
$(test): $(out_base)/tests/.test


# Install.
#
$(install): $(out_base)/xsd/.install           \
            $(out_base)/libxsd/.install        \
	    $(out_base)/examples/.install      \
            $(out_base)/doc/.install
	$(call install-dir,$(src_base)/dist/examples/build,$(install_doc_dir)/xsd/examples/build)
	$(call install-dir,$(src_base)/dist/examples/cxx,$(install_doc_dir)/xsd/examples/cxx,-name makefile)
	$(call install-data,$(src_base)/dist/examples/makefile,$(install_doc_dir)/xsd/examples/makefile)
	$(call install-data,$(src_base)/FLOSSE,$(install_doc_dir)/xsd/FLOSSE)
	$(call install-data,$(src_base)/GPLv2,$(install_doc_dir)/xsd/GPLv2)
	$(call install-data,$(src_base)/LICENSE,$(install_doc_dir)/xsd/LICENSE)
	$(call install-data,$(src_base)/NEWS,$(install_doc_dir)/xsd/NEWS)
	$(call install-data,$(src_base)/dist/README-UNIX,$(install_doc_dir)/xsd/README)


# Dist.
#
$(dist): $(out_base)/xsd/.dist           \
         $(out_base)/libxsd/.dist        \
         $(out_base)/examples/.dist      \
         $(out_base)/doc/.dist
	$(call install-dir,$(src_base)/dist/examples/build,$(dist_prefix)/examples/build)
	$(call install-dir,$(src_base)/dist/examples/cxx,$(dist_prefix)/examples/cxx,-name makefile)
	$(call install-data,$(src_base)/dist/examples/makefile,$(dist_prefix)/examples/makefile)
	$(call install-data,$(src_base)/dist/README-UNIX,$(dist_prefix)/README)
	$(call install-data,$(src_base)/GPLv2,$(dist_prefix)/GPLv2)
	$(call install-data,$(src_base)/FLOSSE,$(dist_prefix)/FLOSSE)
	$(call install-data,$(src_base)/LICENSE,$(dist_prefix)/LICENSE)
	$(call install-data,$(src_base)/NEWS,$(dist_prefix)/NEWS)
	$(call install-data,$(src_base)/version,$(dist_prefix)/version)

$(dist-win): $(dist-pre)                         \
             $(out_base)/xsd/.dist-win           \
             $(out_base)/libxsd/.dist-win        \
             $(out_base)/examples/.dist-win      \
             $(out_base)/doc/.dist-win
	$(call install-dir,$(src_base)/dist/etc,$(dist_prefix)/etc)
	$(call install-dir,$(src_base)/dist/examples/build,$(dist_prefix)/examples/build)
	$(call install-data,$(src_base)/dist/examples/tester.bat,$(dist_prefix)/examples/tester.bat)
	$(call install-data,$(src_base)/dist/examples/makefile,$(dist_prefix)/examples/makefile)
	$(call install-data,$(src_base)/dist/README-WINDOWS,$(dist_prefix)/README.txt)
	$(call message,,todos $(dist_prefix)/README.txt)
	$(call install-data,$(src_base)/dist/README-UNIX,$(dist_prefix)/README-CYGWIN.txt)
	$(call message,,todos $(dist_prefix)/README-CYGWIN.txt)
	$(call install-data,$(src_base)/GPLv2,$(dist_prefix)/GPLv2.txt)
	$(call message,,todos $(dist_prefix)/GPLv2.txt)
	$(call install-data,$(src_base)/FLOSSE,$(dist_prefix)/FLOSSE.txt)
	$(call message,,todos $(dist_prefix)/FLOSSE.txt)
	$(call install-data,$(src_base)/LICENSE,$(dist_prefix)/LICENSE.txt)
	$(call message,,todos $(dist_prefix)/LICENSE.txt)
	$(call install-data,$(src_base)/NEWS,$(dist_prefix)/NEWS.txt)
	$(call message,,todos $(dist_prefix)/NEWS.txt)
	$(call install-data,$(src_base)/version,$(dist_prefix)/version.txt)
	$(call message,,todos $(dist_prefix)/version.txt)

# We need the project files for the examples copied before we try to
# auto-generate the solution files. So each example target that generates
# solutions should depend in order-only on this target.
#
$(dist-pre):
	$(call install-dir,$(src_base)/dist/examples/cxx,$(dist_prefix)/examples/cxx)

# Clean.
#
$(clean): $(out_base)/xsd/.clean      \
          $(out_base)/tests/.clean    \
          $(out_base)/examples/.clean \
          $(out_base)/doc/.clean

$(call include,$(bld_root)/install.make)

$(call import,$(src_base)/xsd/makefile)
$(call import,$(src_base)/libxsd/makefile)
$(call import,$(src_base)/tests/makefile)
$(call import,$(src_base)/examples/makefile)
$(call import,$(src_base)/doc/makefile)

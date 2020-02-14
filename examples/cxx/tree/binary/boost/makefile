# file      : examples/cxx/tree/binary/boost/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../../build/bootstrap.make

xsd := library.xsd
cxx := driver.cxx

obj := $(addprefix $(out_base)/,$(cxx:.cxx=.o) $(xsd:.xsd=.o))
dep := $(obj:.o=.o.d)

driver   := $(out_base)/driver
install  := $(out_base)/.install
dist     := $(out_base)/.dist
dist-win := $(out_base)/.dist-win
clean    := $(out_base)/.clean


# Import.
#
$(call import,\
  $(scf_root)/import/libxerces-c/stub.make,\
  l: xerces_c.l,cpp-options: xerces_c.l.cpp-options)

ifeq ($(filter $(MAKECMDGOALS),dist dist-win install),)
$(call import,\
  $(scf_root)/import/libboost/serialization/stub.make,\
  l: boost_serialization.l,cpp-options: boost_serialization.l.cpp-options)
endif


# Build.
#
$(driver): $(obj) $(xerces_c.l) $(boost_serialization.l)

$(obj) $(dep): cpp_options := -I$(out_base) -I$(src_base) -I$(src_root)/libxsd
$(obj) $(dep): $(xerces_c.l.cpp-options) $(boost_serialization.l.cpp-options)

genf := $(xsd:.xsd=.hxx) $(xsd:.xsd=.ixx) $(xsd:.xsd=.cxx)
gen  := $(addprefix $(out_base)/,$(genf))

$(gen): xsd := $(out_root)/xsd/xsd

$(gen): xsd_options += --generate-ostream \
--hxx-prologue-file $(src_base)/library-prologue.hxx \
--generate-insertion boost::archive::text_oarchive \
--generate-extraction boost::archive::text_iarchive

$(gen): $(out_root)/xsd/xsd

$(call include-dep,$(dep),$(obj),$(gen))

# Convenience alias for default target.
#
$(out_base)/: $(driver)


# Install & Dist.
#
dist-common := $(out_base)/.dist-common

$(install) $(dist) $(dist-win) $(dist-common): path := $(subst $(src_root)/,,$(src_base))

$(install):
	$(call install-data,$(src_base)/README,$(install_doc_dir)/xsd/$(path)/README)
	$(call install-data,$(src_base)/driver.cxx,$(install_doc_dir)/xsd/$(path)/driver.cxx)
	$(call install-data,$(src_base)/library.xsd,$(install_doc_dir)/xsd/$(path)/library.xsd)
	$(call install-data,$(src_base)/library.xml,$(install_doc_dir)/xsd/$(path)/library.xml)
	$(call install-data,$(src_base)/library-prologue.hxx,$(install_doc_dir)/xsd/$(path)/library-prologue.hxx)
	$(call install-data,$(src_base)/boost-archive-extraction.hxx,$(install_doc_dir)/xsd/$(path)/boost-archive-extraction.hxx)
	$(call install-data,$(src_base)/boost-archive-insertion.hxx,$(install_doc_dir)/xsd/$(path)/boost-archive-insertion.hxx)

$(dist-common):
	$(call install-data,$(src_base)/driver.cxx,$(dist_prefix)/$(path)/driver.cxx)
	$(call install-data,$(src_base)/library.xsd,$(dist_prefix)/$(path)/library.xsd)
	$(call install-data,$(src_base)/library.xml,$(dist_prefix)/$(path)/library.xml)
	$(call install-data,$(src_base)/library-prologue.hxx,$(dist_prefix)/$(path)/library-prologue.hxx)
	$(call install-data,$(src_base)/boost-archive-extraction.hxx,$(dist_prefix)/$(path)/boost-archive-extraction.hxx)
	$(call install-data,$(src_base)/boost-archive-insertion.hxx,$(dist_prefix)/$(path)/boost-archive-insertion.hxx)

$(dist): $(dist-common)
	$(call install-data,$(src_base)/README,$(dist_prefix)/$(path)/README)

$(dist-win): |$(out_root)/.dist-pre
$(dist-win): $(dist-common)
	$(call install-data,$(src_base)/README,$(dist_prefix)/$(path)/README.txt)
	$(call message,,todos $(dist_prefix)/$(path)/README.txt)
	$(call meta-vc8sln,$(src_root)/dist/template-vc8.sln,boost-vc8.sln)
	$(call meta-vc9sln,$(src_root)/dist/template-vc9.sln,boost-vc9.sln)
	$(call meta-vc10sln,$(src_root)/dist/template-vc10.sln,boost-vc10.sln)
	$(call meta-vc11sln,$(src_root)/dist/template-vc11.sln,boost-vc11.sln)
	$(call meta-vc12sln,$(src_root)/dist/template-vc12.sln,boost-vc12.sln)


# Clean.
#
$(clean): $(driver).o.clean                            \
  $(addsuffix .cxx.clean,$(obj))                       \
  $(addsuffix .cxx.clean,$(dep))                       \
  $(addprefix $(out_base)/,$(xsd:.xsd=.cxx.xsd.clean))

# Generated .gitignore.
#
ifeq ($(out_base),$(src_base))
$(gen): | $(out_base)/.gitignore
$(driver): | $(out_base)/.gitignore

$(out_base)/.gitignore: files := driver $(genf)
$(clean): $(out_base)/.gitignore.clean

$(call include,$(bld_root)/git/gitignore.make)
endif

# How to.
#
$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)
$(call include,$(scf_root)/xsd/tree/xsd-cxx.make)

$(call include,$(bld_root)/install.make)
$(call include,$(bld_root)/meta/vc8sln.make)
$(call include,$(bld_root)/meta/vc9sln.make)
$(call include,$(bld_root)/meta/vc10sln.make)
$(call include,$(bld_root)/meta/vc11sln.make)
$(call include,$(bld_root)/meta/vc12sln.make)


# Dependencies.
#
$(call import,$(src_root)/xsd/makefile)

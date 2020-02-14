# file      : examples/cxx/tree/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../build/bootstrap.make

all_examples := binary caching embedded custom hello library messaging \
mixed multiroot order performance polymorphism secure streaming wildcard \
compression xpath

build_examples := binary caching embedded custom hello library messaging \
mixed multiroot order performance polymorphism secure streaming wildcard

ifeq ($(xsd_with_zlib),y)
build_examples += compression
endif

ifeq ($(xsd_with_xqilla),y)
build_examples += xpath
endif

default  := $(out_base)/
install  := $(out_base)/.install
dist     := $(out_base)/.dist
dist-win := $(out_base)/.dist-win
clean    := $(out_base)/.clean

# Build.
#
$(default): $(addprefix $(out_base)/,$(addsuffix /,$(build_examples)))

# Install & Dist.
#
$(install) $(dist) $(dist-win): path := $(subst $(src_root)/,,$(src_base))

$(install): $(addprefix $(out_base)/,$(addsuffix /.install,$(all_examples)))
	$(call install-data,$(src_base)/README,$(install_doc_dir)/xsd/$(path)/README)

$(dist): $(addprefix $(out_base)/,$(addsuffix /.dist,$(all_examples)))
	$(call install-data,$(src_base)/README,$(dist_prefix)/$(path)/README)

$(dist-win): export dirs := $(shell find $(src_base) -type d -exec test -f {}/driver.cxx ';' -printf '%P ')
$(dist-win): |$(out_root)/.dist-pre
$(dist-win): $(addprefix $(out_base)/,$(addsuffix /.dist-win,$(all_examples)))
	$(call install-data,$(src_base)/README,$(dist_prefix)/$(path)/README.txt)
	$(call message,,todos $(dist_prefix)/$(path)/README.txt)
	$(call meta-vc8sln,$(src_root)/dist/template-vc8.sln,tree-vc8.sln)
	$(call meta-vc9sln,$(src_root)/dist/template-vc9.sln,tree-vc9.sln)
	$(call meta-vc10sln,$(src_root)/dist/template-vc10.sln,tree-vc10.sln)
	$(call meta-vc11sln,$(src_root)/dist/template-vc11.sln,tree-vc11.sln)
	$(call meta-vc12sln,$(src_root)/dist/template-vc12.sln,tree-vc12.sln)
	$(call meta-vctest,tree-vc8.sln,$(src_root)/dist/examples/test.bat,test.bat)

# Clean.
#
$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(build_examples)))

$(call include,$(bld_root)/install.make)
$(call include,$(bld_root)/meta/vc8sln.make)
$(call include,$(bld_root)/meta/vc9sln.make)
$(call include,$(bld_root)/meta/vc10sln.make)
$(call include,$(bld_root)/meta/vc11sln.make)
$(call include,$(bld_root)/meta/vc12sln.make)
$(call include,$(bld_root)/meta/vctest.make)

ifneq ($(filter $(MAKECMDGOALS),dist dist-win install),)
$(foreach e,$(all_examples),$(call import,$(src_base)/$e/makefile))
else
$(foreach e,$(build_examples),$(call import,$(src_base)/$e/makefile))
endif

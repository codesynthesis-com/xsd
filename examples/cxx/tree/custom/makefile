# file      : examples/cxx/tree/custom/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../build/bootstrap.make

all_examples   := comments contacts double mixed taxonomy wildcard calendar
build_examples := comments contacts double mixed taxonomy wildcard

ifeq ($(xsd_with_boost_date_time),y)
build_examples += calendar
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

$(dist-win): |$(out_root)/.dist-pre
$(dist-win): $(addprefix $(out_base)/,$(addsuffix /.dist-win,$(all_examples)))
	$(call install-data,$(src_base)/README,$(dist_prefix)/$(path)/README.txt)
	$(call message,,todos $(dist_prefix)/$(path)/README.txt)
	$(call meta-vc8sln,$(src_root)/dist/template-vc8.sln,custom-vc8.sln)
	$(call meta-vc9sln,$(src_root)/dist/template-vc9.sln,custom-vc9.sln)
	$(call meta-vc10sln,$(src_root)/dist/template-vc10.sln,custom-vc10.sln)
	$(call meta-vc11sln,$(src_root)/dist/template-vc11.sln,custom-vc11.sln)
	$(call meta-vc12sln,$(src_root)/dist/template-vc12.sln,custom-vc12.sln)


# Clean.
#
$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(build_examples)))

$(call include,$(bld_root)/install.make)
$(call include,$(bld_root)/meta/vc8sln.make)
$(call include,$(bld_root)/meta/vc9sln.make)
$(call include,$(bld_root)/meta/vc10sln.make)
$(call include,$(bld_root)/meta/vc11sln.make)
$(call include,$(bld_root)/meta/vc12sln.make)

ifneq ($(filter $(MAKECMDGOALS),dist dist-win install),)
$(foreach e,$(all_examples),$(call import,$(src_base)/$e/makefile))
else
$(foreach e,$(build_examples),$(call import,$(src_base)/$e/makefile))
endif


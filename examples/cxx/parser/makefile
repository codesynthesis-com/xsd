# file      : examples/cxx/parser/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../build/bootstrap.make

examples := generated hello library mixin mixed multiroot performance \
polymorphism polyroot wildcard

default  := $(out_base)/
install  := $(out_base)/.install
dist     := $(out_base)/.dist
dist-win := $(out_base)/.dist-win
clean    := $(out_base)/.clean

# Build
#
$(default): $(addprefix $(out_base)/,$(addsuffix /,$(examples)))


# Install & Dist.
#
$(install) $(dist) $(dist-win): path := $(subst $(src_root)/,,$(src_base))

$(install): $(addprefix $(out_base)/,$(addsuffix /.install,$(examples)))
	$(call install-data,$(src_base)/README,$(install_doc_dir)/xsd/$(path)/README)

$(dist): $(addprefix $(out_base)/,$(addsuffix /.dist,$(examples)))
	$(call install-data,$(src_base)/README,$(dist_prefix)/$(path)/README)

$(dist-win): export dirs := $(examples)
$(dist-win): |$(out_root)/.dist-pre
$(dist-win): $(addprefix $(out_base)/,$(addsuffix /.dist-win,$(examples)))
	$(call install-data,$(src_base)/README,$(dist_prefix)/$(path)/README.txt)
	$(call message,,todos $(dist_prefix)/$(path)/README.txt)
	$(call meta-vc8sln,$(src_root)/dist/template-vc8.sln,parser-vc8.sln)
	$(call meta-vc9sln,$(src_root)/dist/template-vc9.sln,parser-vc9.sln)
	$(call meta-vc10sln,$(src_root)/dist/template-vc10.sln,parser-vc10.sln)
	$(call meta-vc11sln,$(src_root)/dist/template-vc11.sln,parser-vc11.sln)
	$(call meta-vc12sln,$(src_root)/dist/template-vc12.sln,parser-vc12.sln)
	$(call meta-vctest,parser-vc8.sln,$(src_root)/dist/examples/test.bat,test.bat)

# Clean
#
$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(examples)))

$(call include,$(bld_root)/install.make)
$(call include,$(bld_root)/meta/vc8sln.make)
$(call include,$(bld_root)/meta/vc9sln.make)
$(call include,$(bld_root)/meta/vc10sln.make)
$(call include,$(bld_root)/meta/vc11sln.make)
$(call include,$(bld_root)/meta/vc12sln.make)
$(call include,$(bld_root)/meta/vctest.make)


$(foreach e,$(examples),$(call import,$(src_base)/$e/makefile))

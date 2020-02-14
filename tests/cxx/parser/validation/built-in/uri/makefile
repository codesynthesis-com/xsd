# file      : tests/cxx/parser/validation/built-in/uri/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../../../build/bootstrap.make

cxx := driver.cxx

obj := $(addprefix $(out_base)/,$(cxx:.cxx=.o))
dep := $(obj:.o=.o.d)

driver := $(out_base)/driver
test   := $(out_base)/.test
clean  := $(out_base)/.clean


# Import.
#
$(call import,\
  $(scf_root)/import/libxerces-c/stub.make,\
  l: xerces_c.l,cpp-options: xerces_c.l.cpp-options)

# Build.
#
$(driver): $(obj) $(xerces_c.l)

$(obj) $(dep): cpp_options := -I$(out_base) -I$(src_base) -I$(src_root)/libxsd
$(obj) $(dep): $(xerces_c.l.cpp-options)

# Define XSD_CXX11 since we include libxsd headers directly.
#
$(call include,$(bld_root)/cxx/standard.make) # cxx_standard
ifeq ($(cxx_standard),c++11)
$(obj) $(dep): cpp_options += -DXSD_CXX11
endif

$(call include-dep,$(dep),$(obj),$(gen))

# Convenience alias for default target.
#
$(out_base)/: $(driver)


# Test.
#
$(test): driver := $(driver)
$(test): $(driver)
	$(call message,test $$1,$$1,$(driver))

# Clean.
#
$(clean): $(driver).o.clean                                \
  $(addsuffix .cxx.clean,$(obj))                           \
  $(addsuffix .cxx.clean,$(dep))

# Generated .gitignore.
#
ifeq ($(out_base),$(src_base))
$(driver): | $(out_base)/.gitignore

$(out_base)/.gitignore: files := driver
$(clean): $(out_base)/.gitignore.clean

$(call include,$(bld_root)/git/gitignore.make)
endif

# How to.
#
$(call include,$(bld_root)/cxx/o-e.make)
$(call include,$(bld_root)/cxx/cxx-o.make)
$(call include,$(bld_root)/cxx/cxx-d.make)

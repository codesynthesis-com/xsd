# file      : tests/cxx/tree/order/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../../build/bootstrap.make

xsd := test.xsd
cxx := driver.cxx

obj := $(addprefix $(out_base)/,$(cxx:.cxx=.o) $(xsd:.xsd=.o))
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

genf := $(xsd:.xsd=.hxx) $(xsd:.xsd=.ixx) $(xsd:.xsd=.cxx)
gen  := $(addprefix $(out_base)/,$(genf))

$(gen): xsd := $(out_root)/xsd/xsd
$(gen): xsd_options += --generate-serialization --generate-wildcard \
--generate-comparison \
--ordered-type t1_base --ordered-type t1_derived \
--ordered-type t2_base --ordered-type t2_derived \
--ordered-type t3_type \
--ordered-type t4_base --ordered-type t4_derived \
--ordered-type t5_base --ordered-type t5_derived \
--ordered-type t6_base --ordered-type t6_derived \
--ordered-type t7_type
$(gen): $(out_root)/xsd/xsd

$(call include-dep,$(dep),$(obj),$(gen))

# Convenience alias for default target.
#
$(out_base)/: $(driver)


# Test.
#
$(test): driver := $(driver)
$(test): $(driver) $(src_base)/test.xml $(src_base)/output
	$(call message,test $$1,$$1 $(src_base)/test.xml | diff -u $(src_base)/output -,$(driver))

# Clean.
#
$(clean): $(driver).o.clean                                \
  $(addsuffix .cxx.clean,$(obj))                           \
  $(addsuffix .cxx.clean,$(dep))                           \
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

$(call include,$(bld_root)/cxx/standard.make) # cxx_standard
ifdef cxx_standard
$(gen): xsd_options += --std $(cxx_standard)
$(call include,$(scf_root)/xsd/tree/xsd-cxx.make)
endif


# Dependencies.
#
$(call import,$(src_root)/xsd/makefile)

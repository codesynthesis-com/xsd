# file      : build/bootstrap.make
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

project_name := xsd

# First try to include the bundled bootstrap.make if it exist. If that
# fails, let make search for the external bootstrap.make.
#
build := build-0.3

-include $(dir $(lastword $(MAKEFILE_LIST)))../../$(build)/bootstrap.make

ifeq ($(patsubst %build/bootstrap.make,,$(lastword $(MAKEFILE_LIST))),)
include $(build)/bootstrap.make
endif

def_goal := $(.DEFAULT_GOAL)

# Configuration
#
$(call include,$(scf_root)/configuration.make)

# Include C++ configuration. We need to know if we are using the generic
# C++ compiler in which case we need to compensate for missing dependency
# auto-generation (see below).
#
$(call include,$(bld_root)/cxx/configuration.make)

# Aliases
#
.PHONY: $(out_base)/               \
        $(out_base)/.test          \
        $(out_base)/.install       \
        $(out_base)/.dist          \
        $(out_base)/.dist-win      \
        $(out_base)/.dist-common   \
        $(out_base)/.clean

ifdef %interactive%

.PHONY: test install dist dist-win clean

test: $(out_base)/.test
install: $(out_base)/.install
dist: $(out_base)/.dist
dist-win: $(out_base)/.dist-win
clean: $(out_base)/.clean

endif


# Make sure the distribution prefix is set if the goal is dist or dist-win.
#
ifneq ($(filter $(MAKECMDGOALS),dist dist-win),)
ifeq ($(dist_prefix),)
$(error dist_prefix is not set)
endif
endif

# If we don't have dependency auto-generation then we need to manually
# make sure that generated files are generated before C++ file are
# compiler. To do this we make the object files ($2) depend in order-
# only on generated files ($3).
#
ifeq ($(cxx_id),generic)

define include-dep
$(if $2,$(eval $2: | $3))
endef

else

define include-dep
$(call -include,$1)
endef

endif

# Don't include dependency info for certain targets.
#
ifneq ($(filter $(MAKECMDGOALS),clean disfigure),)
include-dep =
endif


# For dist, install don't include dependencies in examples, and tests
# since we might be cross-compiling.
#
ifneq ($(filter $(MAKECMDGOALS),dist dist-win install),)

ifneq ($(subst $(src_root)/tests/,,$(src_base)),$(src_base))
include-dep =
endif

ifneq ($(subst $(src_root)/examples/,,$(src_base)),$(src_base))
include-dep =
endif

endif

.DEFAULT_GOAL := $(def_goal)

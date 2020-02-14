# file      : tests/cxx/tree/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../build/bootstrap.make

tests :=        \
any-type        \
built-in        \
chameleon       \
comparison      \
compilation     \
complex         \
containment     \
default         \
detach          \
dom-association \
encoding        \
enumeration     \
float           \
list            \
name-clash      \
naming          \
order           \
polymorphism    \
prefix          \
test-template   \
types-only      \
union           \
wildcard

ifeq ($(xsd_with_ace),y)
tests += binary
endif

default   := $(out_base)/
test      := $(out_base)/.test
clean     := $(out_base)/.clean

$(default): $(addprefix $(out_base)/,$(addsuffix /,$(tests)))
$(test): $(addprefix $(out_base)/,$(addsuffix /.test,$(tests)))
$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(tests)))

$(foreach t,$(tests),$(call import,$(src_base)/$t/makefile))

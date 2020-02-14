# file      : doc/cxx/parser/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../build/bootstrap.make

docs := guide

default  := $(out_base)/
install  := $(out_base)/.install
dist     := $(out_base)/.dist
dist-win := $(out_base)/.dist-win
clean    := $(out_base)/.clean

$(default): $(addprefix $(out_base)/,$(addsuffix /,$(docs)))
$(install): $(addprefix $(out_base)/,$(addsuffix /.install,$(docs)))
$(dist): $(addprefix $(out_base)/,$(addsuffix /.dist,$(docs)))
$(dist-win): $(addprefix $(out_base)/,$(addsuffix /.dist-win,$(docs)))
$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(docs)))

$(foreach m,$(docs),$(call import,$(src_base)/$m/makefile))

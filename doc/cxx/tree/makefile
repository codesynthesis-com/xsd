# file      : doc/cxx/tree/makefile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(dir $(lastword $(MAKEFILE_LIST)))../../../build/bootstrap.make

docs := guide manual

default  := $(out_base)/
install  := $(out_base)/.install
dist     := $(out_base)/.dist
dist-win := $(out_base)/.dist-win
clean    := $(out_base)/.clean

# Build.
#
$(default): $(addprefix $(out_base)/,$(addsuffix /,$(docs)))

# Install & Dist.
#
dist-common := $(out_base)/.dist-common

$(install): path := $(subst $(src_root)/doc/,,$(src_base))
$(dist-common): path := $(subst $(src_root)/,,$(src_base))

$(install): $(addprefix $(out_base)/,$(addsuffix /.install,$(docs)))
	$(call install-dir,$(src_base)/reference,$(install_doc_dir)/xsd/$(path)/reference)

$(dist-common):
	$(call install-dir,$(src_base)/reference,$(dist_prefix)/$(path)/reference)

$(dist): $(dist-common) $(addprefix $(out_base)/,$(addsuffix /.dist,$(docs)))
$(dist-win): $(dist-common) $(addprefix $(out_base)/,$(addsuffix /.dist-win,$(docs)))

# Clean.
#
$(clean): $(addprefix $(out_base)/,$(addsuffix /.clean,$(docs)))

$(call include,$(bld_root)/install.make)

$(foreach m,$(docs),$(call import,$(src_base)/$m/makefile))

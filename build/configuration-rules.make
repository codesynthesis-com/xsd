# file      : build/configuration-rules.make
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

$(dcf_root)/configuration-dynamic.make: | $(dcf_root)/.
	$(call message,,$(scf_root)/configure $@)

ifndef %foreign%

disfigure::
	$(call message,rm $$1,rm -f $$1,$(dcf_root)/configuration-dynamic.make)

endif

ifeq ($(.DEFAULT_GOAL),$(dcf_root)/configuration-dynamic.make)
.DEFAULT_GOAL :=
endif

# file      : build/import/libxerces-c/configuration-rules.make
# license   : GNU GPL v2; see accompanying LICENSE file

$(dcf_root)/import/libxerces-c/configuration-dynamic.make: | $(dcf_root)/import/libxerces-c/.
	$(call message,,$(scf_root)/import/libxerces-c/configure $@)

ifndef %foreign%

disfigure::
	$(call message,rm $(dcf_root)/import/libxerces-c/configuration-dynamic.make,\
rm -f $(dcf_root)/import/libxerces-c/configuration-dynamic.make)

endif

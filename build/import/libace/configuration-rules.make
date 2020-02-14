# file      : build/import/libace/configuration-rules.make
# license   : GNU GPL v2; see accompanying LICENSE file

$(dcf_root)/import/libace/configuration-dynamic.make: | $(dcf_root)/import/libace/.
	$(call message,,$(scf_root)/import/libace/configure $@)

ifndef %foreign%

disfigure::
	$(call message,rm $(dcf_root)/import/libace/configuration-dynamic.make,\
rm -f $(dcf_root)/import/libace/configuration-dynamic.make)

endif

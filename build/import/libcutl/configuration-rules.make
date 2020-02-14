# file      : build/import/libcutl/configuration-rules.make
# license   : MIT; see accompanying LICENSE file

$(dcf_root)/import/libcutl/configuration-dynamic.make: | $(dcf_root)/import/libcutl/.
	$(call message,,$(scf_root)/import/libcutl/configure $@)

ifndef %foreign%

$(dcf_root)/.disfigure::
	$(call message,rm $(dcf_root)/import/libcutl/configuration-dynamic.make,\
rm -f $(dcf_root)/import/libcutl/configuration-dynamic.make)

endif

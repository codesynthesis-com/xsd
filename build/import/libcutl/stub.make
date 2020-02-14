# file      : build/import/libcutl/stub.make
# license   : MIT; see accompanying LICENSE file

$(call include-once,$(scf_root)/import/libcutl/configuration-rules.make,$(dcf_root))

libcutl_installed :=

$(call -include,$(dcf_root)/import/libcutl/configuration-dynamic.make)

ifdef libcutl_installed

ifeq ($(libcutl_installed),y)

$(call export,l: -lcutl,cpp-options: )

else

# Include export stub.
#
$(call include,$(scf_root)/export/libcutl/stub.make)

endif

else

.NOTPARALLEL:

endif

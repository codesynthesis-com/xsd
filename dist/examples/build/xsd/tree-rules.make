# file      : examples/build/xsd/tree-rules.make
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

include $(root)/build/xsd/common.make

override LIBS := -lxerces-c $(LIBS)

# Rules.
#
.PRECIOUS: %.cxx %.hxx %.ixx

%.cxx %.hxx %.ixx: %.xsd
	$(XSD) cxx-tree $(XSDFLAGS) $<

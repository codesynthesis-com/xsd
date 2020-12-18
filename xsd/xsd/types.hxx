// file      : xsd/types.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_TYPES_HXX
#define XSD_TYPES_HXX

#include <vector>
#include <cstddef> // std::size_t

#include <libxsd-frontend/types.hxx>

using std::size_t;

using XSDFrontend::String;
using XSDFrontend::NarrowString;

typedef std::vector<NarrowString> NarrowStrings;

#endif // XSD_TYPES_HXX

// file      : xsd/types.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef TYPES_HXX
#define TYPES_HXX

#include <vector>
#include <cstddef> // std::size_t

#include <xsd-frontend/types.hxx>

using std::size_t;

using XSDFrontend::String;
using XSDFrontend::NarrowString;

typedef std::vector<NarrowString> NarrowStrings;

#endif // TYPES_HXX

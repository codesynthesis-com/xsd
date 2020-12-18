// file      : xsd/cxx/literal-map.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_LITERAL_MAP_HXX
#define XSD_CXX_LITERAL_MAP_HXX

#include <map>

#include <xsd/types.hxx>

namespace CXX
{
  typedef std::map<String, String> StringLiteralMap;

  bool
  read_literal_map (NarrowString const& file, StringLiteralMap& map);
}

#endif // XSD_CXX_LITERAL_MAP_HXX

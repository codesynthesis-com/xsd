// file      : xsd/cxx/tree/serialization-source.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_TREE_SERIALIZATION_SOURCE_HXX
#define XSD_CXX_TREE_SERIALIZATION_SOURCE_HXX

#include <xsd/cxx/tree/elements.hxx>

namespace CXX
{
  namespace Tree
  {
    void
    generate_serialization_source (Context&, size_t first, size_t last);
  }
}

#endif  // XSD_CXX_TREE_SERIALIZATION_SOURCE_HXX

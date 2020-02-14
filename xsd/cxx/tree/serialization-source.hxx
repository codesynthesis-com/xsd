// file      : xsd/cxx/tree/serialization-source.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_SERIALIZATION_SOURCE_HXX
#define CXX_TREE_SERIALIZATION_SOURCE_HXX

#include <cxx/tree/elements.hxx>

namespace CXX
{
  namespace Tree
  {
    void
    generate_serialization_source (Context&, size_t first, size_t last);
  }
}

#endif  // CXX_TREE_SERIALIZATION_SOURCE_HXX

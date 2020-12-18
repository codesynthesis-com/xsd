// file      : xsd/cxx/tree/stream-source.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_TREE_STREAM_SOURCE_HXX
#define XSD_CXX_TREE_STREAM_SOURCE_HXX

#include <xsd/cxx/tree/elements.hxx>

namespace CXX
{
  namespace Tree
  {
    void
    generate_stream_source (Context&, size_t first, size_t last);
  }
}

#endif  // XSD_CXX_TREE_STREAM_SOURCE_HXX

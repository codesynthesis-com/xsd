// file      : libxsd/cxx/tree/xdr-stream-common.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_CXX_TREE_XDR_STREAM_COMMON_HXX
#define LIBXSD_CXX_TREE_XDR_STREAM_COMMON_HXX

#include <libxsd/cxx/exceptions.hxx>

namespace xsd
{
  namespace cxx
  {
    namespace tree
    {
      // Base exception for XDR insertion/extraction exceptions.
      //
      struct xdr_stream_operation: xsd::cxx::exception
      {
      };
    }
  }
}

#endif  // LIBXSD_CXX_TREE_XDR_STREAM_COMMON_HXX

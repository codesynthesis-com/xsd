// file      : libxsd/cxx/tree/ace-cdr-stream-common.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_CXX_TREE_ACE_CDR_STREAM_COMMON_HXX
#define LIBXSD_CXX_TREE_ACE_CDR_STREAM_COMMON_HXX

#include <libxsd/cxx/exceptions.hxx>

namespace xsd
{
  namespace cxx
  {
    namespace tree
    {
      // Base exception for ACE CDR insertion/extraction exceptions.
      //
      struct ace_cdr_stream_operation: xsd::cxx::exception
      {
      };
    }
  }
}

#endif  // LIBXSD_CXX_TREE_ACE_CDR_STREAM_COMMON_HXX

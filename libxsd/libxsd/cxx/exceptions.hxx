// file      : libxsd/cxx/exceptions.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_CXX_EXCEPTIONS_HXX
#define LIBXSD_CXX_EXCEPTIONS_HXX

#include <exception> // std::exception

namespace xsd
{
  namespace cxx
  {
    struct exception: std::exception
    {
    };
  }
}

#endif  // LIBXSD_CXX_EXCEPTIONS_HXX

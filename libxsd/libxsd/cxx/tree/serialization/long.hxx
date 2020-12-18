// file      : libxsd/cxx/tree/serialization/long.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_CXX_TREE_SERIALIZATION_LONG_HXX
#define LIBXSD_CXX_TREE_SERIALIZATION_LONG_HXX

#include <sstream>

namespace XERCES_CPP_NAMESPACE
{
  inline void
  operator<< (xercesc::DOMElement& e, long long l)
  {
    std::basic_ostringstream<char> os;
    os << l;
    e << os.str ();
  }

  inline void
  operator<< (xercesc::DOMAttr& a, long long l)
  {
    std::basic_ostringstream<char> os;
    os << l;
    a << os.str ();
  }
}

namespace xsd
{
  namespace cxx
  {
    namespace tree
    {
      template <typename C>
      inline void
      operator<< (list_stream<C>& ls, long long l)
      {
        ls.os_ << l;
      }
    }
  }
}

#endif // LIBXSD_CXX_TREE_SERIALIZATION_LONG_HXX

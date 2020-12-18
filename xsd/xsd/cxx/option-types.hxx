// file      : xsd/cxx/option-types.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_XSD_OPTION_TYPES_HXX
#define XSD_XSD_OPTION_TYPES_HXX

#include <iosfwd>
#include <string>

namespace CXX
{
  struct cxx_version
  {
    enum value
    {
      cxx98,
      cxx11
    };

    cxx_version (value v = value (0)) : v_ (v) {}
    operator value () const {return v_;}

    std::string
    string () const;

  private:
    value v_;
  };

  std::istream&
  operator>> (std::istream&, cxx_version&);
}

#endif // XSD_XSD_OPTION_TYPES_HXX

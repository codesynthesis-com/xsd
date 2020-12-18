// file      : cxx/parser/validation/built-in/uri/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in anyURI type validation.
//
#include <cassert>

// Define XSD_CXX11 since we include libxsd headers directly.
//
#ifdef _MSC_VER
#  if _MSC_VER >= 1600 // VC++10 and later have C++11 always enabled.
#    define XSD_CXX11
#  endif
#else
#  if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
#    define XSD_CXX11
#  endif
#endif

#include <libxsd/cxx/parser/validating/exceptions.hxx>
#include <libxsd/cxx/parser/validating/xml-schema-pimpl.hxx>

using namespace xsd::cxx::parser::validating;

int
main ()
{
  // Good.
  //
  {
    uri_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("  ");
    p._post ();
    assert (p.post_uri () == "");
  }

  {
    uri_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("relative");
    p._post ();
    assert (p.post_uri () == "relative");
  }

  {
    uri_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("#id");
    p._post ();
    assert (p.post_uri () == "#id");
  }

  {
    uri_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("http://www.example.com/foo#bar");
    p._post ();
    assert (p.post_uri () == "http://www.example.com/foo#bar");
  }
}

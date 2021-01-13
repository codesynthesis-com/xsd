// file      : cxx/parser/validation/built-in/qname/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in QName type validation.
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

bool
test_post_fail (qname_pimpl<char>& p)
{
  try
  {
    p._post ();
  }
  catch (invalid_value<char> const&)
  {
    return true;
  }

  return false;
}

int
main ()
{
  typedef xsd::cxx::parser::qname<char> qname;

  // Good.
  //
  {
    qname_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters (" xsi");
    p._characters (":");
    p._characters ("schemaLocation");
    p._post ();
    assert (p.post_qname () == qname ("xsi", "schemaLocation"));
  }

  {
    qname_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("schemaLocation");
    p._post ();
    assert (p.post_qname () == qname ("schemaLocation"));
  }


  // Bad
  //
  {
    qname_pimpl<char> p;
    p.pre ();
    p._pre ();
    //p._characters ("");
    assert (test_post_fail (p));
  }

  {
    qname_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters (":");
    assert (test_post_fail (p));
  }

  {
    qname_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("xsi:");
    assert (test_post_fail (p));
  }

  {
    qname_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters (":schemaLocation");
    assert (test_post_fail (p));
  }

  {
    qname_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("x?i:schemaLocation");
    assert (test_post_fail (p));
  }

  {
    qname_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("xsi:schema Location");
    assert (test_post_fail (p));
  }
}

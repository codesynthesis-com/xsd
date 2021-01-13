// file      : cxx/parser/validation/built-in/boolean/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in boolean type validation.
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
test_post_fail (boolean_pimpl<char>& p)
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
  // Good.
  //
  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("true");
    p._post ();
    assert (p.post_boolean ());
  }

  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("1");
    p._post ();
    assert (p.post_boolean ());
  }

  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("false");
    p._post ();
    assert (!p.post_boolean ());
  }

  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("0");
    p._post ();
    assert (!p.post_boolean ());
  }


  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("  true  ");
    p._post ();
    assert (p.post_boolean ());
  }

  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters (" ");
    p._characters (" \n  ");
    p._characters ("   fa");
    p._characters ("l");
    p._characters ("se   ");
    p._characters (" \n  ");
    p._characters (" ");
    p._post ();
    assert (!p.post_boolean ());
  }

  // Bad
  //
  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    //p._characters ("");
    assert (test_post_fail (p));
  }

  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("");
    assert (test_post_fail (p));
  }

  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("  ");
    assert (test_post_fail (p));
  }

  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("                        ");
    assert (test_post_fail (p));
  }

  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("fal");
    p._characters ("s   ");
    p._characters ("e");
    assert (test_post_fail (p));
  }

  {
    boolean_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("01");
    assert (test_post_fail (p));
  }
}

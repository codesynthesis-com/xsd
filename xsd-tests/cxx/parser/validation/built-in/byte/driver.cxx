// file      : cxx/parser/validation/built-in/byte/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in byte and unsigned byte types validation.
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

template <typename T>
bool
test_post_fail (T& p)
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
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("123");
    p._post ();
    assert (p.post_byte () == 123);
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("\t +123 \n ");
    p._post ();
    assert (p.post_byte () == 123);
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-123");
    p._post ();
    assert (p.post_byte () == -123);
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("+123");
    p._post ();
    assert (p.post_byte () == 123);
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("0000000000000000123");
    p._post ();
    assert (p.post_byte () == 123);
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("+0000000000000000123");
    p._post ();
    assert (p.post_byte () == 123);
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-0000000000000000123");
    p._post ();
    assert (p.post_byte () == -123);
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("\t \n");
    p._characters (" -");
    p._characters ("00000");
    p._characters ("001");
    p._characters ("23   \n\t");
    p._post ();
    assert (p.post_byte () == -123);
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-128");
    p._post ();
    assert (p.post_byte () == -128);
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("127");
    p._post ();
    assert (p.post_byte () == 127);
  }

  {
    unsigned_byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("+123");
    p._post ();
    assert (p.post_unsigned_byte () == 123);
  }

  {
    unsigned_byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("0");
    p._post ();
    assert (p.post_unsigned_byte () == 0);
  }

  {
    unsigned_byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("255");
    p._post ();
    assert (p.post_unsigned_byte () == 255);
  }

  // Bad
  //
  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    // p._characters ("");
    assert (test_post_fail (p));
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("");
    assert (test_post_fail (p));
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters (" \n \t ");
    assert (test_post_fail (p));
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("+");
    assert (test_post_fail (p));
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-");
    assert (test_post_fail (p));
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("++01");
    assert (test_post_fail (p));
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("--01");
    assert (test_post_fail (p));
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-01");
    p._characters ("    ");
    p._characters ("23    ");
    assert (test_post_fail (p));
  }

  {
    unsigned_byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-123");
    assert (test_post_fail (p));
  }

  // Ranges
  //
  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-129");
    assert (test_post_fail (p));
  }

  {
    byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("128");
    assert (test_post_fail (p));
  }

  {
    unsigned_byte_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("256");
    assert (test_post_fail (p));
  }
}

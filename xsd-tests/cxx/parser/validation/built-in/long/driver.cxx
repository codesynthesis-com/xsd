// file      : cxx/parser/validation/built-in/long/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in long and unsigned long types validation.
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
    long_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-9223372036854775808");
    p._post ();
    assert (p.post_long () == (-9223372036854775807LL - 1));
  }

  {
    long_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("0");
    p._post ();
    assert (p.post_long () == 0);
  }

  {
    long_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("9223372036854775807");
    p._post ();
    assert (p.post_long () == 9223372036854775807LL);
  }

  {
    unsigned_long_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("0");
    p._post ();
    assert (p.post_unsigned_long () == 0);
  }

  {
    unsigned_long_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("18446744073709551615");
    p._post ();
    assert (p.post_unsigned_long () == 18446744073709551615ULL);
  }

  // Bad
  //

  {
    unsigned_long_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-123");
    assert (test_post_fail (p));
  }


  // Ranges
  //
  {
    long_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-9223372036854775809");
    assert (test_post_fail (p));
  }

  {
    long_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("9223372036854775808");
    assert (test_post_fail (p));
  }

  {
    unsigned_long_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("18446744073709551616");
    assert (test_post_fail (p));
  }
}

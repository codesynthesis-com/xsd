// file      : cxx/parser/validation/built-in/short/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in short and unsigned short types validation.
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
    short_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-32768");
    p._post ();
    assert (p.post_short () == -32768);
  }

  {
    short_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("0");
    p._post ();
    assert (p.post_short () == 0);
  }

  {
    short_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("32767");
    p._post ();
    assert (p.post_short () == 32767);
  }

  {
    unsigned_short_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("0");
    p._post ();
    assert (p.post_unsigned_short () == 0);
  }

  {
    unsigned_short_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("65535");
    p._post ();
    assert (p.post_unsigned_short () == 65535);
  }

  // Bad
  //

  {
    unsigned_short_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-1234");
    assert (test_post_fail (p));
  }


  // Ranges
  //
  {
    short_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-32769");
    assert (test_post_fail (p));
  }

  {
    short_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("32768");
    assert (test_post_fail (p));
  }

  {
    unsigned_short_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("65536");
    assert (test_post_fail (p));
  }
}

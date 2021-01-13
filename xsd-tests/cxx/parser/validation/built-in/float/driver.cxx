// file      : cxx/parser/validation/built-in/float/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the built-in float, double, and decimal types validation.
//
#include <math.h>
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

  // float
  //
  {
    float_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters (" 0000123.456 ");
    p._post ();
    assert (p.post_float () == 123.456F);
  }

  {
    float_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-12.345E2");
    p._post ();
    assert (p.post_float () == -12.345E2F);
  }

  {
    float_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("0");
    p._post ();
    assert (p.post_float () == 0.0F);
  }

  {
    float_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-0");
    p._post ();
    assert (p.post_float () == -0.0F);
  }

  {
    float_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("INF");
    p._post ();
    assert (isinf (p.post_float ()));
  }

  {
    float_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-INF");
    p._post ();
    assert (isinf (p.post_float ()));
  }

  {
    float_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("NaN");
    p._post ();
    assert (isnan (p.post_float ()));
  }

  // double
  //
  {
    double_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters (" 0000123.456789 ");
    p._post ();
    assert (p.post_double () == 123.456789);
  }

  {
    double_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-12.3456789E2");
    p._post ();
    assert (p.post_double () == -12.3456789E2);
  }

  {
    double_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("0");
    p._post ();
    assert (p.post_double () == 0.0);
  }

  {
    double_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-0");
    p._post ();
    assert (p.post_double () == -0.0);
  }

  {
    double_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("INF");
    p._post ();
    assert (isinf (p.post_double ()));
  }

  {
    double_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-INF");
    p._post ();
    assert (isinf (p.post_double ()));
  }

  {
    double_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("NaN");
    p._post ();
    assert (isnan (p.post_double ()));
  }

  // decimal
  //
  {
    decimal_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters (" 0000123.456789 ");
    p._post ();
    assert (p.post_decimal () == 123.456789);
  }

  {
    decimal_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-123.45678912345");
    p._post ();
    assert (p.post_decimal () == -123.45678912345);
  }

  {
    decimal_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("0");
    p._post ();
    assert (p.post_decimal () == 0.0);
  }

  {
    decimal_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-0");
    p._post ();
    assert (p.post_decimal () == -0.0);
  }


  // Bad
  //

  // float
  //
  // Note that some standard libraries recognize the [+-](INF|INFINITY)
  // strings (notably libc++) and some of them don't (notably libstdc++; see
  // LWG #2381 for details).
  //
#if 0
  {
    float_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("+INF");
    assert (test_post_fail (p));
  }
#endif

  {
    float_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("1.45 E2");
    assert (test_post_fail (p));
  }

  // double
  //
#if 0
  {
    double_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("+INF");
    assert (test_post_fail (p));
  }
#endif

  {
    double_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("1.45 E2");
    assert (test_post_fail (p));
  }

  // decimal
  //
  {
    decimal_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("INF");
    assert (test_post_fail (p));
  }

  {
    decimal_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("+INF");
    assert (test_post_fail (p));
  }

  {
    decimal_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("-INF");
    assert (test_post_fail (p));
  }

  {
    decimal_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("NaN");
    assert (test_post_fail (p));
  }

  {
    decimal_pimpl<char> p;
    p.pre ();
    p._pre ();
    p._characters ("1.45 2");
    assert (test_post_fail (p));
  }
}

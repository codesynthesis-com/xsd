// file      : tests/cxx/tree/complex/ctor/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test generation of varous complex type constructors.
//

#include <cassert>
#include <memory>

#include "test.hxx"

#ifdef XSD_CXX11
#  include <utility> // std::move
#  define XSD_MOVE(x) std::move(x)
#else
#  define XSD_MOVE(x) x
#endif

using namespace std;
using namespace test;

int
main ()
{
  // Test case A.
  //
  {
    a_base b1;
    a_base b2 ("abc");        // empty ultimate base + required
    a_base b3 ("abc", "foo"); // ultimate base + required

    a_derived a1;
    a_derived a2 ("foo", "bar");        // empty ultimate base + required
    a_derived a3 (b3, "bar");           // base + required
    a_derived a4 ("abc", "foo", "bar"); // ultimate base + required
  }

  // Test case B.
  //
  {
    b_simple s ("base");
    b_base b ("base", "foo");
    b_derived d ("base", "foo", "bar");
    b_type t ("base");
  }

  // Test case C.
  //
  {
    c_simple s (c_enum::a);
    c_base b (c_enum::a, "foo");
    c_derived d (c_enum::a, "foo", "bar");
    c_type t (c_enum::a);
  }

  // Test case D.
  //
  {
    d_simple s (1);
    d_base b (1, "foo");
    d_derived d (1, "foo", "bar");
    d_type t (1);
  }

  // Test case E.
  //
  {
    // e_base
    //
    e_base b1 (1, "foo", e_complex_type ("bar"));

    XSD_AUTO_PTR<e_complex_type> c2 (new e_complex_type ("bar"));
    e_base b2 (1, "foo", XSD_MOVE (c2));

    XSD_AUTO_PTR<e_simple_type> s3 (new e_simple_type ("foo"));
    XSD_AUTO_PTR<e_complex_type> c3 (new e_complex_type ("bar"));
    e_base b3 (1, XSD_MOVE (s3), XSD_MOVE (c3));

    assert (b1 == b2);
    assert (b1 == b3);

    // e_derived
    //
    e_derived d1 (1, "foo", e_complex_type ("bar"),
                  true, "baz", e_complex_type ("biz"));

    XSD_AUTO_PTR<e_complex_type> c2a (new e_complex_type ("bar"));
    XSD_AUTO_PTR<e_complex_type> c2b (new e_complex_type ("biz"));
    e_derived d2 (1, "foo", XSD_MOVE (c2a), true, "baz", XSD_MOVE (c2b));

    XSD_AUTO_PTR<e_simple_type> s3a (new e_simple_type ("foo"));
    XSD_AUTO_PTR<xml_schema::string> s3b (new xml_schema::string ("baz"));
    XSD_AUTO_PTR<e_complex_type> c3a (new e_complex_type ("bar"));
    XSD_AUTO_PTR<e_complex_type> c3b (new e_complex_type ("biz"));
    e_derived d3 (1,
                  XSD_MOVE (s3a),
                  XSD_MOVE (c3a),
                  true,
                  XSD_MOVE (s3b),
                  XSD_MOVE (c3b));

    assert (d1 == d2);
    assert (d1 == d3);

  }

  // Test case F.
  //
  {
    f_type f1 (xml_schema::type (), 1, "foo", f_complex_type ("bar"));

    XSD_AUTO_PTR<f_complex_type> c2 (new f_complex_type ("bar"));
    f_type f2 (1, "foo", XSD_MOVE (c2));

    XSD_AUTO_PTR<f_simple_type> s3 (new f_simple_type ("foo"));
    XSD_AUTO_PTR<f_complex_type> c3 (new f_complex_type ("bar"));
    f_type f3 (1, XSD_MOVE (s3), XSD_MOVE (c3));

    assert (f1 == f2);
    assert (f1 == f3);
  }
}

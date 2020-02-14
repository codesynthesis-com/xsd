// file      : tests/cxx/tree/polymorphism/comparison/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test comparison of polymorphic object models.
//

#include <memory> // std::auto_ptr/unique_ptr
#include <sstream>
#include <iostream>

#include "test.hxx"

using namespace std;
using namespace test;

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

  try
  {
    XSD_AUTO_PTR<type> r (root (argv[1]));

    // Equals.
    //
    {
      derived1 d ("a", 1);
      d.b ("b");
      type r1 (d);

      assert (*r == r1);
    }

    // Values are not equal.
    //
    {
      derived1 d ("a", 1);
      d.b ("c");
      type r1 (d);

      assert (*r != r1);
    }

    // Values are not equal.
    //
    {
      derived1 d ("a", 2);
      d.b ("b");
      type r1 (d);

      assert (*r != r1);
    }

    // Different types.
    //
    {
      derived2 d ("a", 1);
      d.c ().push_back ("c");
      type r1 (d);

      assert (*r != r1);
    }

    xml_schema::namespace_infomap map;

    map["t"].name = "test";

    stringstream s;
    root (s, *r, map);

    XSD_AUTO_PTR<type> c (root (s, xml_schema::flags::dont_validate));

    assert (*r == *c);
  }
  catch (xml_schema::exception const& e)
  {
    cerr << e << endl;
    return 1;
  }
}

// file      : cxx/tree/default/general/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test default attribute/element values.
//

#include <memory> // std::auto_ptr/unique_ptr
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
    XSD_AUTO_PTR<type> r (root (argv[1], xml_schema::flags::dont_validate));

    xml_schema::namespace_infomap map;
    map["t"].name = "test";
    root (cout, *r, map);
  }
  catch (xml_schema::exception const& e)
  {
    cerr << e << endl;
    return 1;
  }
}

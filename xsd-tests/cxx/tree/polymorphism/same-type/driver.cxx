// file      : cxx/tree/polymorphism/same-type/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test substitution group and xsi:type that don't change the type.
//

#include <memory> // std::auto_ptr/unique_ptr
#include <iostream>

#include "test.hxx"

#undef NDEBUG
#include <cassert>

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

    cout << *r << endl;
  }
  catch (xml_schema::exception const& e)
  {
    cerr << e << endl;
    return 1;
  }
}

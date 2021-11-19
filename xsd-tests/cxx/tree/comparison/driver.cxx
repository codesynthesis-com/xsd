// file      : cxx/tree/comparison/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test generated comparison operators.
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

    type::complex_sequence s (r->complex ());

    assert (s[0] == s[0]);
    assert (s[0] != s[1]);
  }
  catch (xml_schema::exception const& e)
  {
    cerr << e << endl;
    return 1;
  }
}

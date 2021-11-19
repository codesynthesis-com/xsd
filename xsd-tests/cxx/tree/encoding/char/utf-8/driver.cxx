// file      : cxx/tree/encoding/char/utf-8/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test UTF-8 encoding.
//

#include <memory> // std::auto_ptr/unique_ptr
#include <fstream>
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

    {
      type::a_sequence const& s (r->a ());

      if (s[0] != "abc" ||
          s[1] != "\xD5\x95" ||
          s[2] != "\xEA\xAA\xAA")
      {
        cerr << "invalid encoding" << endl;
        return 1;
      }
    }

    {
      type::b_sequence const& s (r->b ());

      if (s[0] != strenum::abc ||
          s[1] != strenum::a_c ||
          s[2] != strenum::cxx_bc)
      {
        cerr << "invalid encoding" << endl;
        return 1;
      }
    }

    xml_schema::namespace_infomap map;
    map["t"].name = "test";

    root (std::cout, *r, map, "ASCII");
  }
  catch (xml_schema::exception const& e)
  {
    cerr << "xml_schema::exception: " << e.what () << endl;
    return 1;
  }
}

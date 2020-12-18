// file      : cxx/tree/encoding/wchar/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test the wide character mapping.
//

#include <memory> // std::auto_ptr/unique_ptr
#include <fstream>
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
    // Use dont_validate because we do not have instance's system id (path).
    //
    std::ifstream ifs (argv[1]);
    XSD_AUTO_PTR<type> r (root (ifs, xml_schema::flags::dont_validate));

    {
      type::b_sequence const& s (r->b ());

      if (s[0] != strenum::abc ||
          s[1] != strenum::a__c ||
          s[2] != strenum::cxx__bc ||
          s[3] != strenum::ab__)
      {
        cerr << "invalid encoding" << endl;
        return 1;
      }
    }

    xml_schema::namespace_infomap map;
    map[L"t"].name = L"test";

    root (std::cout, *r, map, L"ASCII");
  }
  catch (xml_schema::exception const& e)
  {
    cerr << "xml_schema::exception: " << e.what () << endl;
    return 1;
  }
}

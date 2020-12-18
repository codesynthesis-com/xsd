// file      : cxx/tree/dom-association/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test DOM association/ownership.
//

#include <memory> // std::auto_ptr/unique_ptr
#include <fstream>
#include <iostream>

#include <xercesc/dom/DOM.hpp>

#include "dom-parse.hxx"
#include "test.hxx"

using namespace std;
using namespace test;
using namespace xercesc;

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

  int r (0);

  XMLPlatformUtils::Initialize ();

  try
  {
    ifstream ifs;
    ifs.exceptions (ifstream::badbit | ifstream::failbit);
    ifs.open (argv[1]);

    DOMDocument* ptr;

#ifdef XSD_CXX11
    xml_schema::dom::unique_ptr<DOMDocument> doc (parse (ifs, argv[1], true));
    ptr = doc.get ();
    unique_ptr<type> r (
      root (std::move (doc),
            xml_schema::flags::keep_dom | xml_schema::flags::own_dom));
#else
    xml_schema::dom::auto_ptr<DOMDocument> doc (parse (ifs, argv[1], true));
    ptr = doc.get ();
    auto_ptr<type> r (
      root (doc,
            xml_schema::flags::keep_dom | xml_schema::flags::own_dom));
#endif

    assert (doc.get () == 0);
    assert (r->_node ()->getOwnerDocument () == ptr);
  }
  catch (xml_schema::exception const& e)
  {
    cerr << e << endl;
    r = 1;
  }
  catch (const std::ios_base::failure&)
  {
    cerr << argv[1] << ": unable to open or read failure" << endl;
    r = 1;
  }

  XMLPlatformUtils::Terminate ();
  return r;
}

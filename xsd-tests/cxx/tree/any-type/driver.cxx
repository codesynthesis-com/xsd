// file      : cxx/tree/any-type/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test anyType and anySimpleType content extraction.
//

#include <memory>  // std::auto_ptr/unique_ptr
#include <utility> // std::move
#include <sstream>
#include <iostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "test.hxx" // Get XSD_CXX11 defined.

#include <libxsd/cxx/xml/string.hxx>

using namespace std;
using namespace test;
using namespace xercesc;

namespace xml = xsd::cxx::xml;

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

  XMLPlatformUtils::Initialize ();

  try
  {
    // Test parsing
    //
    XSD_AUTO_PTR<type> r (root (argv[1]));

    // Test API.
    //
    {
      assert (type::a_default_value ().text_content () == "default value");
    }

    {
      xml_schema::simple_type x ("fox");
      assert (x.text_content () == "fox");
      x.text_content ("foo");
      assert (x.text_content () == "foo");
      x.text_content ().clear ();
      assert (x.text_content () == "");
      x.text_content () = "baz";
      r->s ().push_back (x);
    }

    {
      xml_schema::type x;

      DOMDocument& doc (x.dom_content_document ());

      // Copy.
      //
      DOMElement* e (doc.createElement (xml::string ("dummy").c_str ()));
      e->setAttribute (xml::string ("x").c_str (),
                       xml::string ("foo").c_str ());
      e->setTextContent (xml::string ("data").c_str ());
      x.dom_content ().set (*e);
      e->release ();

      r->t ().push_back (x);
    }

    {
      XSD_AUTO_PTR<xml_schema::type> x (new xml_schema::type);

      DOMDocument& doc (x->dom_content_document ());

      // Assume ownership.
      //
      DOMElement* e (doc.createElement (xml::string ("dummy").c_str ()));
      e->setAttribute (xml::string ("x").c_str (),
                       xml::string ("foo").c_str ());
      e->setTextContent (xml::string ("data").c_str ());
      x->dom_content ().set (e);

#ifdef XSD_CXX11
      r->t ().push_back (std::move (x));
#else
      r->t ().push_back (x);
#endif
    }

    // Test printing.
    //
    cout << *r << endl
         << endl;

    // Test serialization.
    //
    xml_schema::namespace_infomap map;

    map["t"].name   = "test";
    map["t"].schema = "test.xsd";
    map["o"].name   = "other";

    stringstream iostr;
    root (iostr, *r, map);

    cout << iostr.str () << endl
         << endl;

    {
      XSD_AUTO_PTR<type> r1 (root (iostr, argv[1]));

      // Xerces-C++ mis-indentation of mixed content messes this up.
      // assert (*r == *r);

      stringstream iostr;
      root (iostr, *r1, map);

      cout << iostr.str () << endl
           << endl;
    }

    // Test comparison.
    //
    assert (*r == *r);

    // Test copy c-tor.
    //
    type copy (*r);
    assert (copy == *r);
  }
  catch (xml_schema::exception const& e)
  {
    cerr << e << endl;
    return 1;
  }

  XMLPlatformUtils::Terminate ();
}

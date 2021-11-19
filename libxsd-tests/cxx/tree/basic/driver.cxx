// file      : cxx/tree/basic/driver.cxx
// copyright : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <iostream>

#include <xercesc/dom/DOMText.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMDocument.hpp>

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

#include <xsd/cxx/xml/qualified-name.hxx>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>       // XSD_DOM_AUTO_PTR
#include <xsd/cxx/xml/dom/elements.hxx>       // name()
#include <xsd/cxx/xml/dom/parsing-source.hxx> // parser, parse()

#include <xsd/cxx/tree/text.hxx>          // text_content()
#include <xsd/cxx/tree/parsing.hxx>
#include <xsd/cxx/tree/elements.hxx>      // auto_initializer, properties
#include <xsd/cxx/tree/exceptions.hxx>    // parsing
#include <xsd/cxx/tree/error-handler.hxx>

#undef NDEBUG
#include <cassert>

using namespace std;
using namespace xsd::cxx;

// Usage: argv[0] <xml-file>
//
// Parse the specified XML file using the XML DOM parser and print the element
// names and values to stdout.
//
int
main (int argc, char* argv[])
{
  assert (argc == 2);

  xml::auto_initializer ai;

  tree::error_handler<char> h;
  tree::properties<char> ps;

  XSD_DOM_AUTO_PTR<xercesc::DOMDocument> d (
    xml::dom::parse<char> (argv[1], h, ps, 0 /* flags */));

  h.throw_if_failed<tree::parsing<char>> (); // Abort on error.

  xml::dom::parser<char> p (*d->getDocumentElement (), true, false, false);
  for (; p.more_content (); p.next_content (false /* text */))
  {
    const xercesc::DOMElement&      i (p.cur_element ());
    const xml::qualified_name<char> n (xml::dom::name<char> (i));
    cout << n.name () << ' ' << tree::text_content<char> (i) << endl;
  }
}

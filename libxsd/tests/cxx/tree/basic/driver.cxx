// file      : tests/cxx/tree/basic/driver.cxx
// copyright : GNU GPL v2 + exceptions; see accompanying LICENSE file

//#include <memory>   // std::auto_ptr/unique_ptr
#include <cassert>
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

#include <libxsd/cxx/xml/qualified-name.hxx>

#include <libxsd/cxx/xml/dom/auto-ptr.hxx>       // XSD_DOM_AUTO_PTR
#include <libxsd/cxx/xml/dom/elements.hxx>       // name()
#include <libxsd/cxx/xml/dom/parsing-source.hxx> // parser, parse()

#include <libxsd/cxx/tree/text.hxx>          // text_content()
#include <libxsd/cxx/tree/parsing.hxx>
#include <libxsd/cxx/tree/elements.hxx>      // auto_initializer, properties
#include <libxsd/cxx/tree/exceptions.hxx>    // parsing
#include <libxsd/cxx/tree/error-handler.hxx>

using namespace std;
using namespace xsd::cxx;

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

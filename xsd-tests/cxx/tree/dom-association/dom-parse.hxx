// file      : cxx/tree/dom-association/dom-parse.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef DOM_PARSE
#define DOM_PARSE

#include <string>
#include <iosfwd>

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

#include <libxsd/cxx/xml/dom/auto-ptr.hxx>

// Parse an XML document from the standard input stream with an
// optional resource id. Resource id is used in diagnostics as
// well as to locate schemas referenced from inside the document.
//
XSD_DOM_AUTO_PTR<xercesc::DOMDocument>
parse (std::istream& is,
       const std::string& id,
       bool validate);

#endif // DOM_PARSE

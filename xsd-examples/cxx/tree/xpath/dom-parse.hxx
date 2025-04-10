// file      : cxx/tree/xpath/dom-parse.hxx
// copyright : not copyrighted - public domain

#ifndef DOM_PARSE
#define DOM_PARSE

#include <string>
#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMImplementation.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

// Parse an XML document from the standard input stream with an
// optional resource id. Resource id is used in diagnostics as
// well as to locate schemas referenced from inside the document.
//
xsd::cxx::xml::dom::unique_ptr<xercesc::DOMDocument>
parse (std::istream& is,
       const std::string& id,
       bool validate,
       xercesc::DOMImplementation*);

#endif // DOM_PARSE

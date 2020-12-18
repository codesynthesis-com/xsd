// file      : xsd/cxx/parser/parser-header.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_PARSER_PARSER_HEADER_HXX
#define XSD_CXX_PARSER_PARSER_HEADER_HXX

#include <xsd/cxx/parser/elements.hxx>

namespace CXX
{
  namespace Parser
  {
    void
    generate_parser_header (Context&, bool generate_xml_schema);
  }
}

#endif  // XSD_CXX_PARSER_PARSER_HEADER_HXX

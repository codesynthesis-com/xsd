// file      : xsd/type-map/parser.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_TYPE_MAP_PARSER_HXX
#define XSD_TYPE_MAP_PARSER_HXX

#include <xsd/types.hxx>

#include <xsd/type-map/type-map.hxx>
#include <xsd/type-map/lexer.hxx>

namespace TypeMap
{
  class Parser
  {
  public:
    Parser (Lexer&, String const& path);

    // Merge parsed namespaces.
    //
    bool
    parse (Namespaces&);

  private:
    bool
    namespace_ (Namespaces&);

    bool
    include (Namespace&);

    bool
    type (Lexer::Token, Namespace&);

  private:
    Lexer& lex_;
    String path_;
    std::wostream& e;
  };
}

#endif // XSD_TYPE_MAP_PARSER_HXX

// file      : xsd/type-map/lexer.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_TYPE_MAP_LEXER_HXX
#define XSD_TYPE_MAP_LEXER_HXX

#include <locale>
#include <iosfwd>

#include <xsd/types.hxx>

namespace TypeMap
{
  class Lexer
  {
  public:
    class Token
    {
    public:
      enum Type
      {
        token,
        punct,
        eos
      };

      Token (Type type, String const& lexeme, size_t line)
          : type_ (type), lexeme_ (lexeme), line_ (line)
      {
      }

      Type
      type () const
      {
        return type_;
      }

      String const&
      lexeme () const
      {
        return lexeme_;
      }

      size_t
      line () const
      {
        return line_;
      }

    private:
      Type type_;
      String lexeme_;
      size_t line_;
    };

    Lexer (std::istream&, String const& path);

    struct Failed {};

    Token
    next ();

  private:
    std::locale locale_;
    std::istream& is_;
    String path_;
    size_t line_;
    String held_lexeme_;
    bool comment_;
  };

}

#endif // XSD_TYPE_MAP_LEXER_HXX

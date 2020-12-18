// file      : xsd/options-parser.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_OPTIONS_PARSER_HXX
#define XSD_OPTIONS_PARSER_HXX

#include <xsd/types.hxx>
#include <xsd/options.hxx>

namespace cli
{
  template <>
  struct parser<NarrowString>
  {
    static void
    parse (NarrowString& x, bool& xs, scanner& s)
    {
      xs = true;
      const char* o (s.next ());

      if (s.more ())
        x = s.next ();
      else
        throw missing_value (o);
    }
  };
}

#endif // XSD_OPTIONS_PARSER_HXX

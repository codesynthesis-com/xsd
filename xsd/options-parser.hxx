// file      : xsd/options-parser.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef OPTIONS_PARSER_HXX
#define OPTIONS_PARSER_HXX

#include <types.hxx>
#include <options.hxx>

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

#endif // OPTIONS_PARSER_HXX

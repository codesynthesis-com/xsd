// file      : cxx/tree/naming/camel/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test camel case (upper for types, lower for functions) naming style.
//

#include <sstream>
#include <iostream>

#include <xercesc/util/PlatformUtils.hpp>

#include "test.hxx"

using namespace std;
using namespace test;

int
main ()
{
  xercesc::XMLPlatformUtils::Initialize ();

  try
  {
    // Enum 'value' type.
    //
    {
      Gender::Value v;
      v = Gender::female;
      XSD_UNUSED (v);
    }

    // Anonymous type.
    //
    {
      Foo f ("a", "b");

      if (f.a () != "a" || f.b () != "b")
        return 1;
    }

    // Type name and accessors/modifiers.
    //
    {
      Type t ("bar");

      // foo
      //
      {
        Type::FooType* p = 0;
        XSD_UNUSED (p);

        Type::FooOptional o;

        if (t.foo ().present ())
          return 1;

        t.foo (o);
      }

      // bar
      //
      {
        Type::BarType* p = 0;
        XSD_UNUSED (p);

        if (t.bar () != "bar")
          return 1;

        t.bar ("barbar");
      }

      // baz
      //
      {
        Type::BazType* p = 0;
        XSD_UNUSED (p);

        Type::BazSequence s;
        Type::BazIterator i (s.begin ());
        Type::BazConstIterator ci (s.begin ());
        XSD_UNUSED (i);
        XSD_UNUSED (ci);

        if (t.baz () != s)
          return 1;

        t.baz (s);
      }

      // any
      //
      {
        Type::AnySequence s (t.domDocument ());
        Type::AnyIterator i (s.begin ());
        Type::AnyConstIterator  ci (s.begin ());
        XSD_UNUSED (i);
        XSD_UNUSED (ci);

        if (t.any () != s)
          return 1;

        t.any (s);
      }

      // foo
      //
      {
        Type::FoxType x = Type::foxDefaultValue ();

        if (t.fox () != x)
          return 1;

        t.fox ("fox");
      }

      // any_attribute
      //
      {
        Type::AnyAttributeSet s (t.domDocument ());
        Type::AnyAttributeIterator i (s.begin ());
        Type::AnyAttributeConstIterator ci (s.begin ());
        XSD_UNUSED (i);
        XSD_UNUSED (ci);

        if (t.anyAttribute () != s)
          return 1;

        t.anyAttribute (s);
      }
    }

    // Parsing/serialization functions.
    //
    {
      istringstream is ("<t:Root xmlns:t='test'>foo</t:Root>");
      root (is, xml_schema::Flags::dont_validate);
    }

    {
      ostringstream os;
      xml_schema::NamespaceInfomap m;
      m["t"].name = "test";

      root (os, "foo", m);
    }
  }
  catch (xml_schema::Exception const& e)
  {
    cerr << e << endl;
    return 1;
  }

  xercesc::XMLPlatformUtils::Terminate ();
}

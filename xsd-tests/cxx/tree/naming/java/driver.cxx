// file      : cxx/tree/naming/java/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test Java naming style.
//

#include <sstream>
#include <iostream>

#include <xercesc/util/PlatformUtils.hpp>

#include "test.hxx"

#undef NDEBUG
#include <cassert>

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

      if (f.getA () != "a" || f.getB () != "b")
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

        if (t.getFoo ().present ())
          return 1;

        t.setFoo (o);
      }

      // bar
      //
      {
        Type::BarType* p = 0;
        XSD_UNUSED (p);

        if (t.getBar () != "bar")
          return 1;

        t.setBar ("barbar");
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

        if (t.getBaz () != s)
          return 1;

        t.setBaz (s);
      }

      // any
      //
      {
        Type::AnySequence s (t.getDomDocument ());
        Type::AnyIterator i (s.begin ());
        Type::AnyConstIterator  ci (s.begin ());
        XSD_UNUSED (i);
        XSD_UNUSED (ci);

        if (t.getAny () != s)
          return 1;

        t.setAny (s);
      }

      // foo
      //
      {
        Type::FoxType x = Type::getFoxDefaultValue ();

        if (t.getFox () != x)
          return 1;

        t.setFox ("fox");
      }

      // any_attribute
      //
      {
        Type::AnyAttributeSet s (t.getDomDocument ());
        Type::AnyAttributeIterator i (s.begin ());
        Type::AnyAttributeConstIterator ci (s.begin ());
        XSD_UNUSED (i);
        XSD_UNUSED (ci);

        if (t.getAnyAttribute () != s)
          return 1;

        t.setAnyAttribute (s);
      }
    }

    // Parsing/serialization functions.
    //
    {
      istringstream is ("<t:root xmlns:t='test'>foo</t:root>");
      parseRoot (is, xml_schema::Flags::dont_validate);
    }

    {
      ostringstream os;
      xml_schema::NamespaceInfomap m;
      m["t"].name = "test";

      serializeRoot (os, "foo", m);
    }
  }
  catch (xml_schema::Exception const& e)
  {
    cerr << e << endl;
    return 1;
  }

  xercesc::XMLPlatformUtils::Terminate ();
}

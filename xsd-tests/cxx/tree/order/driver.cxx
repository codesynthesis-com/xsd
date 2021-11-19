// file      : cxx/tree/order/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test ordered type support.
//

#include <memory> // std::auto_ptr/unique_ptr
#include <iostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "test.hxx"

#undef NDEBUG
#include <cassert>

using namespace std;
using namespace test;
using namespace xercesc;

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " test.xml" << endl;
    return 1;
  }

  XMLPlatformUtils::Initialize ();

  try
  {
    XSD_AUTO_PTR<root> r (root_ (argv[1], xml_schema::flags::dont_initialize));

    root c (*r);
    assert (c == *r);

    for (root::t1_const_iterator j (r->t1 ().begin ());
         j != r->t1 ().end (); ++j)
    {
      const t1_derived& d (*j);

      for (t1_derived::content_order_const_iterator i (
             d.content_order ().begin ()); i != d.content_order ().end (); ++i)
      {
        cout << i->id << ' ' << i->index << endl;
      }
    }

    xml_schema::namespace_infomap map;

    map["t"].name = "test";
    map["t1"].name = "test1";

    root_ (cout, *r, map, "UTF-8", xml_schema::flags::dont_initialize);
  }
  catch (xml_schema::exception const& e)
  {
    cerr << e << endl;
    return 1;
  }

  XMLPlatformUtils::Terminate ();
}

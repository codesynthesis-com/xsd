// file      : cxx/tree/containment/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test tree node containment.
//

#include <memory> // std::auto_ptr/unique_ptr
#include <cassert>

#include "test.hxx"

#ifdef XSD_CXX11
#  include <utility> // std::move
#  define XSD_MOVE(x) std::move(x)
#else
#  define XSD_MOVE(x) x
#endif

using namespace std;
using namespace test;

int
main ()
{
  // Change of a container in a sub-tree without ID.
  //
  {
    XSD_AUTO_PTR<inner> i (new inner ());
    i->ref ("foo");

    outer o;
    o.i (XSD_MOVE (i));
    o.ref ("foo");

    assert (o.i ()->ref ()->get () == 0);
    assert (o.ref ()->get () == 0);
  }

  // Change of container in a sub-tree with ID inside.
  //
  {
    XSD_AUTO_PTR<inner> i (new inner ());
    inner* p (i.get ());
    i->id ("foo");
    i->ref ("foo");
    assert (i->ref ()->get () == p);

    outer o;
    o.i (XSD_MOVE (i));
    o.ref ("foo");

    assert (o.i ()->ref ()->get () == p);
    assert (o.ref ()->get () == p);
  }

  // Change of a container in ID.
  //
  {
    XSD_AUTO_PTR<xml_schema::id> id (new xml_schema::id ("foo"));

    inner i;
    i.id (XSD_MOVE (id));
    i.ref ("foo");
    assert (i.ref ()->get () == &i);
  }

  // Change of a container in a type derived from ID with ID inside.
  //
  {
    XSD_AUTO_PTR<id_ex> id (new id_ex ("foo"));
    id_ex* p (id.get ());
    id->id ("bar");

    inner i;
    i.id_ex (XSD_MOVE (id));

    i.ref ("foo");
    assert (i.ref ()->get () == &i);

    i.ref ("bar");
    assert (i.ref ()->get () == p);
  }

  // IDREF lists
  //
  {
    id i1 ("a"), i2 ("b");

    XSD_AUTO_PTR<ids> ic (new ids);
    ic->id ().push_back (i1);
    ic->id ().push_back (i2);

    XSD_AUTO_PTR<xml_schema::idrefs> r1 (new xml_schema::idrefs);
    r1->push_back (xml_schema::idref ("a"));
    r1->push_back (xml_schema::idref ("b"));

    XSD_AUTO_PTR<idref_list> r2 (new idref_list);
    r2->push_back (xml_schema::idref ("a"));
    r2->push_back (xml_schema::idref ("b"));

    XSD_AUTO_PTR<idrefs1> rc1 (new idrefs1);
    XSD_AUTO_PTR<idrefs2> rc2 (new idrefs2);

    rc1->idrefs (XSD_MOVE (r1));
    rc2->idrefs (XSD_MOVE (r2));

    model m;
    m.ids (XSD_MOVE (ic));
    m.idrefs1 (XSD_MOVE (rc1));
    m.idrefs2 (XSD_MOVE (rc2));

    assert (m.idrefs1 ().idrefs ()[0].get () != 0);
    assert (m.idrefs1 ().idrefs ()[1].get () != 0);

    assert (m.idrefs2 ().idrefs ()[0].get () != 0);
    assert (m.idrefs2 ().idrefs ()[1].get () != 0);
  }
}

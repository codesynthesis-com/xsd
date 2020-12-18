// file      : cxx/tree/custom/calendar/driver.cxx
// copyright : not copyrighted - public domain

#include <memory>   // std::auto_ptr/std::unique_ptr
#include <iostream>

#include <libxsd/cxx/config.hxx> // XSD_AUTO_PTR

#include "calendar.hxx"

using std::cerr;
using std::endl;

int
main (int argc, char* argv[])
{
  if (argc != 2)
  {
    cerr << "usage: " << argv[0] << " calendar.xml" << endl;
    return 1;
  }

  try
  {
    using namespace calendar;

    XSD_AUTO_PTR<events> e (events_ (argv[1]));

    for (events::event_const_iterator i (e->event ().begin ());
         i != e->event ().end (); ++i)
    {
      cerr << i->date () << " " << i->title () << endl
           << *i << endl;
    }
  }
  catch (const xml_schema::exception& e)
  {
    cerr << e << endl;
    return 1;
  }
}

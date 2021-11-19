// file      : cxx/tree/built-in/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test built-in type mapping.
//

#include <memory>  // std::auto_ptr/unique_ptr
#include <sstream>
#include <iostream>

#include "types.hxx"

#undef NDEBUG
#include <cassert>

using std::cerr;
using std::endl;

int
main (int argc, char* argv[])
{
  if (argc != 4)
  {
    cerr << "usage: " << argv[0] << " elements.xml attributes.xml inherited.xml" << endl;
    return 1;
  }

  XSD_AUTO_PTR<xmlns::test::Elements> elements (
    xmlns::test::elements (argv[1]));

  XSD_AUTO_PTR<xmlns::test::Attributes> attributes (
    xmlns::test::attributes (argv[2]));

  XSD_AUTO_PTR<xmlns::test::Inherited> inherited (
    xmlns::test::inherited (argv[3]));

  cerr << "elements:" << *elements << endl
       << endl
       << "attributes:" << *attributes << endl
       << endl
       << "inherited:" << *inherited << endl;

  // Test parsing/serialization.
  //

  xml_schema::namespace_infomap map;

  map["test"].name = "http://www.codesynthesis.com/xmlns/test";
  map["test"].schema = "types.xsd";

  {
    std::ostringstream ostr;
    xmlns::test::elements (ostr, *elements, map);

    std::istringstream istr (ostr.str ());
    XSD_AUTO_PTR<xmlns::test::Elements> elements1 (
      xmlns::test::elements (istr));

    std::ostringstream ostr1;
    xmlns::test::elements (ostr1, *elements1, map);

    if (ostr.str () != ostr1.str ())
      return 1;
  }

  {
    std::ostringstream ostr;
    xmlns::test::attributes (ostr, *attributes, map);

    std::istringstream istr (ostr.str ());
    XSD_AUTO_PTR<xmlns::test::Attributes> attributes1 (
      xmlns::test::attributes (istr));

    std::ostringstream ostr1;
    xmlns::test::attributes (ostr1, *attributes1, map);

    if (ostr.str () != ostr1.str ())
      return 1;
  }

  {
    std::ostringstream ostr;
    xmlns::test::inherited (ostr, *inherited, map);

    std::istringstream istr (ostr.str ());
    XSD_AUTO_PTR<xmlns::test::Inherited> inherited1 (
      xmlns::test::inherited (istr));

    std::ostringstream ostr1;
    xmlns::test::inherited (ostr1, *inherited1, map);

    if (ostr.str () != ostr1.str ())
      return 1;
  }
}

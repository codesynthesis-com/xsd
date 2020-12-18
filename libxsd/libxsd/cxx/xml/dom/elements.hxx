// file      : libxsd/cxx/xml/dom/elements.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_CXX_XML_DOM_ELEMENTS_HXX
#define LIBXSD_CXX_XML_DOM_ELEMENTS_HXX

#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include <libxsd/cxx/xml/qualified-name.hxx>

namespace xsd
{
  namespace cxx
  {
    namespace xml
    {
      namespace dom
      {
        template <typename C>
        qualified_name<C>
        name (const xercesc::DOMAttr&);

        template <typename C>
        qualified_name<C>
        name (const xercesc::DOMElement&);
      }
    }
  }
}

#include <libxsd/cxx/xml/dom/elements.txx>

#endif // LIBXSD_CXX_XML_DOM_ELEMENTS_HXX

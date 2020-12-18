// file      : libxsd/cxx/xml/dom/wildcard-source.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_CXX_XML_DOM_WILDCARD_SOURCE_HXX
#define LIBXSD_CXX_XML_DOM_WILDCARD_SOURCE_HXX

#include <xercesc/dom/DOMDocument.hpp>

#include <libxsd/cxx/xml/dom/auto-ptr.hxx>

namespace xsd
{
  namespace cxx
  {
    namespace xml
    {
      namespace dom
      {
        template <typename C>
        XSD_DOM_AUTO_PTR<xercesc::DOMDocument>
        create_document ();
      }
    }
  }
}

#include <libxsd/cxx/xml/dom/wildcard-source.txx>

#endif // LIBXSD_CXX_XML_DOM_WILDCARD_SOURCE_HXX

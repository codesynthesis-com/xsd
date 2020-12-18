// file      : libxsd/cxx/tree/text.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_CXX_TREE_TEXT_HXX
#define LIBXSD_CXX_TREE_TEXT_HXX

#include <string>

#include <xercesc/dom/DOMElement.hpp>

namespace xsd
{
  namespace cxx
  {
    namespace tree
    {
      // Throws expected_text_content.
      //
      template <typename C>
      std::basic_string<C>
      text_content (const xercesc::DOMElement&);
    }
  }
}

#include <libxsd/cxx/tree/text.txx>

#endif // LIBXSD_CXX_TREE_TEXT_HXX

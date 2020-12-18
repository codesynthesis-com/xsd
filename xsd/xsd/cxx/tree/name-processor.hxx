// file      : xsd/cxx/tree/name-processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_TREE_NAME_PROCESSOR_HXX
#define XSD_CXX_TREE_NAME_PROCESSOR_HXX

#include <xsd/types.hxx>

#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/options.hxx>

namespace CXX
{
  namespace Tree
  {
    class NameProcessor
    {
    public:
      bool
      process (options const&,
               XSDFrontend::SemanticGraph::Schema&,
               XSDFrontend::SemanticGraph::Path const& file,
               StringLiteralMap const&);
    };
  }
}

#endif // XSD_CXX_TREE_NAME_PROCESSOR_HXX

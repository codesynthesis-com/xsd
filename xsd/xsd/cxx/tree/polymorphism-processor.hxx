// file      : xsde/cxx/tree/polymorphism-processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_TREE_POLYMORPHISM_PROCESSOR_HXX
#define XSD_CXX_TREE_POLYMORPHISM_PROCESSOR_HXX

#include <libxsd-frontend/semantic-graph.hxx>

#include <xsd/xsd.hxx>
#include <xsd/types.hxx>

#include <xsd/cxx/tree/options.hxx>

namespace CXX
{
  namespace Tree
  {
    class PolymorphismProcessor
    {
    public:
      bool
      process (options const&,
               XSDFrontend::SemanticGraph::Schema&,
               XSDFrontend::SemanticGraph::Path const& file,
               const WarningSet& disabled_warnings);
    };
  }
}

#endif // XSD_CXX_TREE_POLYMORPHISM_PROCESSOR_HXX

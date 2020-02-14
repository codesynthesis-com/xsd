// file      : xsde/cxx/tree/polymorphism-processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_POLYMORPHISM_PROCESSOR_HXX
#define CXX_TREE_POLYMORPHISM_PROCESSOR_HXX

#include <xsd-frontend/semantic-graph.hxx>

#include <xsd.hxx>
#include <types.hxx>

#include <cxx/tree/options.hxx>

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

#endif // CXX_TREE_POLYMORPHISM_PROCESSOR_HXX

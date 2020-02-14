// file      : xsde/cxx/tree/order-processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_ORDER_PROCESSOR_HXX
#define CXX_TREE_ORDER_PROCESSOR_HXX

#include <xsd-frontend/semantic-graph.hxx>

#include <xsd.hxx>
#include <types.hxx>

#include <cxx/tree/options.hxx>

namespace CXX
{
  namespace Tree
  {
    class OrderProcessor
    {
    public:
      bool
      process (options const&,
               XSDFrontend::SemanticGraph::Schema&,
               XSDFrontend::SemanticGraph::Path const& file);
    };
  }
}

#endif // CXX_TREE_ORDER_PROCESSOR_HXX

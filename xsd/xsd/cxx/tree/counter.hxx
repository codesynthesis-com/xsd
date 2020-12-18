// file      : xsd/cxx/tree/counter.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_TREE_COUNTER_HXX
#define XSD_CXX_TREE_COUNTER_HXX

#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/options.hxx>

namespace CXX
{
  namespace Tree
  {
    class Counter
    {
    public:
      Counts
      count (options const&,
             SemanticGraph::Schema&,
             SemanticGraph::Path const&);
    };
  }
}

#endif // XSD_CXX_TREE_COUNTER_HXX

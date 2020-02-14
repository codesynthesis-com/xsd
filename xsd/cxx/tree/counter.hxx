// file      : xsd/cxx/tree/counter.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_COUNTER_HXX
#define CXX_TREE_COUNTER_HXX

#include <cxx/tree/elements.hxx>
#include <cxx/tree/options.hxx>

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

#endif // CXX_TREE_COUNTER_HXX

// file      : xsd/cxx/tree/name-processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_NAME_PROCESSOR_HXX
#define CXX_TREE_NAME_PROCESSOR_HXX

#include <types.hxx>

#include <cxx/tree/elements.hxx>
#include <cxx/tree/options.hxx>

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

#endif // CXX_TREE_NAME_PROCESSOR_HXX

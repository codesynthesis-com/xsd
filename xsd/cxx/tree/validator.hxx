// file      : xsd/cxx/tree/validator.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_TREE_VALIDATOR_HXX
#define CXX_TREE_VALIDATOR_HXX

#include <cxx/tree/elements.hxx>
#include <cxx/tree/options.hxx>

#include <xsd.hxx>

namespace CXX
{
  namespace Tree
  {
    class Validator
    {
    public:
      bool
      validate (options const&,
                SemanticGraph::Schema&,
                SemanticGraph::Path const& tu,
                const WarningSet& disabled_warnings,
                Counts const& counts);
    };
  }
}

#endif  // CXX_TREE_VALIDATOR_HXX

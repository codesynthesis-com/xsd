// file      : xsd/cxx/tree/validator.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_TREE_VALIDATOR_HXX
#define XSD_CXX_TREE_VALIDATOR_HXX

#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/options.hxx>

#include <xsd/xsd.hxx>

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

#endif  // XSD_CXX_TREE_VALIDATOR_HXX

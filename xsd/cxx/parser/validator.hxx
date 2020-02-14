// file      : xsd/cxx/parser/validator.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_PARSER_VALIDATOR_HXX
#define CXX_PARSER_VALIDATOR_HXX

#include <xsd.hxx>
#include <types.hxx>

#include <cxx/parser/elements.hxx>
#include <cxx/parser/options.hxx>

namespace CXX
{
  namespace Parser
  {
    class Validator
    {
    public:
      bool
      validate (options const&,
                SemanticGraph::Schema&,
                SemanticGraph::Path const& tu,
                bool gen_driver,
                const WarningSet& disabled_warnings);
    };
  }
}

#endif  // CXX_PARSER_VALIDATOR_HXX

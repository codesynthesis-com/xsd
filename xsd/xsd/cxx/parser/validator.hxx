// file      : xsd/cxx/parser/validator.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_PARSER_VALIDATOR_HXX
#define XSD_CXX_PARSER_VALIDATOR_HXX

#include <xsd/xsd.hxx>
#include <xsd/types.hxx>

#include <xsd/cxx/parser/elements.hxx>
#include <xsd/cxx/parser/options.hxx>

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

#endif  // XSD_CXX_PARSER_VALIDATOR_HXX

// file      : xsd/cxx/parser/name-processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_PARSER_NAME_PROCESSOR_HXX
#define CXX_PARSER_NAME_PROCESSOR_HXX

#include <xsd-frontend/semantic-graph.hxx>

#include <types.hxx>

#include <cxx/elements.hxx>
#include <cxx/parser/options.hxx>

namespace CXX
{
  namespace Parser
  {
    class NameProcessor
    {
    public:
      void
      process (options const&,
               XSDFrontend::SemanticGraph::Schema&,
               XSDFrontend::SemanticGraph::Path const& file,
               StringLiteralMap const& map);
    };
  }
}

#endif // CXX_PARSER_NAME_PROCESSOR_HXX

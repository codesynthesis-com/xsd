// file      : xsd/cxx/parser/name-processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_PARSER_NAME_PROCESSOR_HXX
#define XSD_CXX_PARSER_NAME_PROCESSOR_HXX

#include <libxsd-frontend/semantic-graph.hxx>

#include <xsd/types.hxx>

#include <xsd/cxx/elements.hxx>
#include <xsd/cxx/parser/options.hxx>

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

#endif // XSD_CXX_PARSER_NAME_PROCESSOR_HXX

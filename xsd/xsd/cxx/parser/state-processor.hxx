// file      : xsd/cxx/parser/state-processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_PARSER_STATE_PROCESSOR_HXX
#define XSD_CXX_PARSER_STATE_PROCESSOR_HXX

#include <libxsd-frontend/semantic-graph.hxx>

#include <xsd/types.hxx>

namespace CXX
{
  namespace Parser
  {
    class StateProcessor
    {
    public:
      void
      process (XSDFrontend::SemanticGraph::Schema&,
               XSDFrontend::SemanticGraph::Path const& file);
    };
  }
}

#endif // XSD_CXX_PARSER_STATE_PROCESSOR_HXX

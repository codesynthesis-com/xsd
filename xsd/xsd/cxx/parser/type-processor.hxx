// file      : xsd/cxx/parser/type-processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_PARSER_TYPE_PROCESSOR_HXX
#define XSD_CXX_PARSER_TYPE_PROCESSOR_HXX

#include <libxsd-frontend/semantic-graph.hxx>

#include <xsd/types.hxx>

#include <xsd/type-map/type-map.hxx>

#include <xsd/cxx/parser/options.hxx>

namespace CXX
{
  namespace Parser
  {
    class TypeProcessor
    {
    public:
      void
      process (options const&,
               XSDFrontend::SemanticGraph::Schema&,
               bool gen_driver,
               TypeMap::Namespaces&);
    };
  }
}

#endif // XSD_CXX_PARSER_TYPE_PROCESSOR_HXX

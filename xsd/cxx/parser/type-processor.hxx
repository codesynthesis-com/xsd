// file      : xsd/cxx/parser/type-processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_PARSER_TYPE_PROCESSOR_HXX
#define CXX_PARSER_TYPE_PROCESSOR_HXX

#include <xsd-frontend/semantic-graph.hxx>

#include <types.hxx>

#include <type-map/type-map.hxx>

#include <cxx/parser/options.hxx>

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

#endif // CXX_PARSER_TYPE_PROCESSOR_HXX

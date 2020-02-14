// file      : xsd/cxx/parser/generator.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef CXX_PARSER_GENERATOR_HXX
#define CXX_PARSER_GENERATOR_HXX

#include <xsd-frontend/semantic-graph/elements.hxx> // Path
#include <xsd-frontend/semantic-graph/schema.hxx>

#include <xsd.hxx>
#include <types.hxx>

#include <cxx/literal-map.hxx>
#include <cxx/parser/options.hxx>

namespace CXX
{
  namespace Parser
  {
    class Generator
    {
    public:
      static void
      usage ();

      struct Failed {};

      static size_t
      generate (options const&,
                XSDFrontend::SemanticGraph::Schema&,
                XSDFrontend::SemanticGraph::Path const& file,
                bool file_per_type,
                StringLiteralMap const&,
                bool gen_driver,
                const WarningSet& disabled_warnings,
                FileList& file_list,
                AutoUnlinks& unlinks);

    private:
      Generator ();
    };
  }
}

#endif // CXX_PARSER_GENERATOR_HXX

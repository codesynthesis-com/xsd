// file      : xsd/cxx/tree/generator.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_TREE_GENERATOR_HXX
#define XSD_CXX_TREE_GENERATOR_HXX

#include <libxsd-frontend/semantic-graph/elements.hxx> // Path
#include <libxsd-frontend/semantic-graph/schema.hxx>

#include <xsd/xsd.hxx>
#include <xsd/types.hxx>

#include <xsd/cxx/literal-map.hxx>
#include <xsd/cxx/tree/options.hxx>

namespace CXX
{
  namespace Tree
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
                const WarningSet& disabled_warnings,
                FileList& file_list,
                AutoUnlinks& unlinks);

    private:
      Generator ();
    };
  }
}

#endif // XSD_CXX_TREE_GENERATOR_HXX

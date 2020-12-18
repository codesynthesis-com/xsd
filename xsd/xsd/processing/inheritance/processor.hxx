// file      : xsd/processing/inheritance/processor.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_PROCESSING_INHERITANCE_PROCESSOR_HXX
#define XSD_PROCESSING_INHERITANCE_PROCESSOR_HXX

#include <libxsd-frontend/semantic-graph/elements.hxx> // Path
#include <libxsd-frontend/semantic-graph/schema.hxx>

#include <xsd/types.hxx>

namespace Processing
{
  namespace Inheritance
  {
    class Processor
    {
    public:
      struct Failed {};

      void
      process (XSDFrontend::SemanticGraph::Schema&,
               XSDFrontend::SemanticGraph::Path const& file);
    };
  }
}

#endif // XSD_PROCESSING_INHERITANCE_PROCESSOR_HXX

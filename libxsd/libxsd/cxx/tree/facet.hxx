// file      : libxsd/cxx/tree/facet.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_CXX_TREE_FACET_HXX
#define LIBXSD_CXX_TREE_FACET_HXX

namespace xsd
{
  namespace cxx
  {
    namespace tree
    {
      // We need to keep this type POD in order to be able to create a
      // static array.
      //
      struct facet
      {
        enum id_type
        {
          none,
          total_digits,
          fraction_digits
        };

        id_type id;
        unsigned long value;

        static const facet*
        find (const facet* facets, facet::id_type id)
        {
          while (facets->id != id && facets->id != none)
            ++facets;

          return facets->id != none ? facets : 0;
        }
      };
    }
  }
}

#endif  // LIBXSD_CXX_TREE_FACET_HXX

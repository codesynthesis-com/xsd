// file      : libxsd/cxx/tree/parsing/byte.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_CXX_TREE_PARSING_BYTE_HXX
#define LIBXSD_CXX_TREE_PARSING_BYTE_HXX

#include <libxsd/cxx/ro-string.hxx>
#include <libxsd/cxx/zc-istream.hxx>

#include <libxsd/cxx/xml/string.hxx> // xml::transcode

#include <libxsd/cxx/tree/text.hxx>  // text_content

namespace xsd
{
  namespace cxx
  {
    namespace tree
    {
      template <typename C>
      struct traits<signed char, C, schema_type::other>
      {
        typedef signed char type;

        static type
        create (const xercesc::DOMElement& e, flags f, container* c);

        static type
        create (const xercesc::DOMAttr& a, flags f, container* c);

        static type
        create (const std::basic_string<C>& s,
                const xercesc::DOMElement*,
                flags,
                container*);
      };

      template <typename C>
      signed char traits<signed char, C, schema_type::other>::
      create (const xercesc::DOMElement& e, flags f, container* c)
      {
        return create (tree::text_content<C> (e), 0, f, c);
      }

      template <typename C>
      signed char traits<signed char, C, schema_type::other>::
      create (const xercesc::DOMAttr& a, flags f, container* c)
      {
        return create (xml::transcode<C> (a.getValue ()), 0, f, c);
      }

      template <typename C>
      signed char traits<signed char, C, schema_type::other>::
      create (const std::basic_string<C>& s,
              const xercesc::DOMElement*,
              flags,
              container*)
      {
        // This type cannot have whitespaces in its values. As result we
        // don't need to waste time collapsing whitespaces. All we need to
        // do is trim the string representation which can be done without
        // copying.
        //
        ro_string<C> tmp (s);
        trim (tmp);

        zc_istream<C> is (tmp);

        short t;
        is >> t;

        return static_cast<type> (t);
      }
    }
  }
}

#endif // LIBXSD_CXX_TREE_PARSING_BYTE_HXX

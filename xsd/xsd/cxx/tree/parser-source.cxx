// file      : xsd/cxx/tree/parser-source.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd/cxx/tree/parser-source.hxx>

#include <libxsd-frontend/semantic-graph.hxx>
#include <libxsd-frontend/traversal.hxx>

namespace CXX
{
  namespace Tree
  {
    namespace
    {
      struct ElementFunction: Traversal::Element,
                              GlobalElementBase,
                              Context
      {
        ElementFunction (Context& c)
            : GlobalElementBase (c), Context (c)
        {
        }

        virtual void
        traverse (Type& e)
        {
          if (!doc_root_p (e))
            return;

          SemanticGraph::Type& t (e.type ());

          // Check if we need to handle xsi:type and substitution groups.
          // If this element's type is anonymous then we don't need to do
          // anything.
          //
          bool poly (polymorphic && polymorphic_p (t) && !anonymous_p (t));

          // Check if this element is abstract.
          //
          bool abst;
          {
            SemanticGraph::Complex* tc;
            abst = (tc = dynamic_cast<SemanticGraph::Complex*> (&t)) != 0 &&
              tc->abstract_p ();
          }

          // Nothing to do if we are abstract and not polymorphic.
          //
          if (abst && !polymorphic)
            return;

          String const& name (eparser (e));
          String type (type_name (e));
          String const& error_handler (error_handler_type);

          // Note that I am using fq-name in function calls because g++ gets
          // confused if the name is 'type'. (see tests/schema/anonymous)
          //

          char const* d (std >= cxx_version::cxx11 ? "std::move (d)" : "d");

          // URI.
          //
          os << auto_ptr << "< " << type << " >" << endl
             << name << " (const " << string_type << "& u," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << "::xsd::cxx::xml::auto_initializer i (" << endl
             << "(f & " << flags_type << "::dont_initialize) == 0," << endl
             << "(f & " << flags_type << "::keep_dom) == 0);"
             << endl
             << "::xsd::cxx::tree::error_handler< " << char_type << " > h;"
             << endl
             << dom_auto_ptr << "< " << xerces_ns <<
            "::DOMDocument > d (" << endl
             << "::xsd::cxx::xml::dom::parse< " << char_type << " > (" << endl
             << "u, h, p, f";

          if (options.disable_multi_import ())
            os << " | ::xsd::cxx::xml::dom::no_muliple_imports";

          os << "));"
             << endl
             << "h.throw_if_failed< ::xsd::cxx::tree::parsing< " <<
            char_type << " > > ();"
             << endl
             << "return " << auto_ptr << "< " << type << " > (" << endl
             << fq_name (e, "parser") << " (" << endl
             << d << ", f | " << flags_type << "::own_dom, p));"
             << "}";

          os << auto_ptr << "< " << type << " >" << endl
             << name << " (const " << string_type << "& u," << endl
             << error_handler << "& h," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << "::xsd::cxx::xml::auto_initializer i (" << endl
             << "(f & " << flags_type << "::dont_initialize) == 0," << endl
             << "(f & " << flags_type << "::keep_dom) == 0);"
             << endl
             << dom_auto_ptr << "< " << xerces_ns <<
            "::DOMDocument > d (" << endl
             << "::xsd::cxx::xml::dom::parse< " << char_type << " > (" << endl
             << "u, h, p, f";

          if (options.disable_multi_import ())
            os << " | ::xsd::cxx::xml::dom::no_muliple_imports";

          os << "));"
             << endl
             << "if (!d.get ())" << endl
             << "throw ::xsd::cxx::tree::parsing< " << char_type << " > ();"
             << endl
             << "return " << auto_ptr << "< " << type << " > (" << endl
             << fq_name (e, "parser") << " (" << endl
             << d << ", f | " << flags_type << "::own_dom, p));"
             << "}";

          os << auto_ptr << "< " << type << " >" << endl
             << name << " (const " << string_type << "& u," << endl
             << xerces_ns << "::DOMErrorHandler& h," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << dom_auto_ptr << "< " << xerces_ns <<
            "::DOMDocument > d (" << endl
             << "::xsd::cxx::xml::dom::parse< " << char_type << " > (" << endl
             << "u, h, p, f";

          if (options.disable_multi_import ())
            os << " | ::xsd::cxx::xml::dom::no_muliple_imports";

          os << "));"
             << endl
             << "if (!d.get ())" << endl
             << "throw ::xsd::cxx::tree::parsing< " << char_type << " > ();"
             << endl
             << "return " << auto_ptr << "< " << type << " > (" << endl
             << fq_name (e, "parser") << " (" << endl
             << d << ", f | " << flags_type << "::own_dom, p));"
             << "}";


          // istream
          //
          os << auto_ptr << "< " << type << " >" << endl
             << name << " (::std::istream& is," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << "::xsd::cxx::xml::auto_initializer i (" << endl
             << "(f & " << flags_type << "::dont_initialize) == 0," << endl
             << "(f & " << flags_type << "::keep_dom) == 0);"
             << endl
             << "::xsd::cxx::xml::sax::std_input_source isrc (is);"
             << "return " << fq_name (e, "parser") << " (isrc, f, p);"
             << "}";

          os << auto_ptr << "< " << type << " >" << endl
             << name << " (::std::istream& is," << endl
             << error_handler << "& h," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << "::xsd::cxx::xml::auto_initializer i (" << endl
             << "(f & " << flags_type << "::dont_initialize) == 0," << endl
             << "(f & " << flags_type << "::keep_dom) == 0);"
             << endl
             << "::xsd::cxx::xml::sax::std_input_source isrc (is);"
             << "return " << fq_name (e, "parser") << " (isrc, h, f, p);"
             << "}";

          os << auto_ptr << "< " << type << " >" << endl
             << name << " (::std::istream& is," << endl
             << xerces_ns << "::DOMErrorHandler& h," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << "::xsd::cxx::xml::sax::std_input_source isrc (is);"
             << "return " << fq_name (e, "parser") << " (isrc, h, f, p);"
             << "}";

          os << auto_ptr << "< " << type << " >" << endl
             << name << " (::std::istream& is," << endl
             << "const " << string_type << "& sid," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << "::xsd::cxx::xml::auto_initializer i (" << endl
             << "(f & " << flags_type << "::dont_initialize) == 0," << endl
             << "(f & " << flags_type << "::keep_dom) == 0);"
             << endl
             << "::xsd::cxx::xml::sax::std_input_source isrc (is, sid);"
             << "return " << fq_name (e, "parser") << " (isrc, f, p);"
             << "}";

          os << auto_ptr << "< " << type << " >" << endl
             << name << " (::std::istream& is," << endl
             << "const " << string_type << "& sid," << endl
             << error_handler << "& h," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << "::xsd::cxx::xml::auto_initializer i (" << endl
             << "(f & " << flags_type << "::dont_initialize) == 0," << endl
             << "(f & " << flags_type << "::keep_dom) == 0);"
             << endl
             << "::xsd::cxx::xml::sax::std_input_source isrc (is, sid);"
             << "return " << fq_name (e, "parser") << " (isrc, h, f, p);"
             << "}";

          os << auto_ptr << "< " << type << " >" << endl
             << name << " (::std::istream& is," << endl
             << "const " << string_type << "& sid," << endl
             << xerces_ns << "::DOMErrorHandler& h," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << "::xsd::cxx::xml::sax::std_input_source isrc (is, sid);"
             << "return " << fq_name (e, "parser") << " (isrc, h, f, p);"
             << "}";


          // InputSource.
          //
          os << auto_ptr << "< " << type << " >" << endl
             << name << " (" << xerces_ns << "::InputSource& i," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << "::xsd::cxx::tree::error_handler< " << char_type << " > h;"
             << endl
             << dom_auto_ptr << "< " << xerces_ns <<
            "::DOMDocument > d (" << endl
             << "::xsd::cxx::xml::dom::parse< " << char_type << " > (" << endl
             << "i, h, p, f";

          if (options.disable_multi_import ())
            os << " | ::xsd::cxx::xml::dom::no_muliple_imports";

          os << "));"
             << endl
             << "h.throw_if_failed< ::xsd::cxx::tree::parsing< " <<
            char_type << " > > ();"
             << endl
             << "return " << auto_ptr << "< " << type << " > (" << endl
             << fq_name (e, "parser") << " (" << endl
             << d << ", f | " << flags_type << "::own_dom, p));"
             << "}";

          os << auto_ptr << "< " << type << " >" << endl
             << name << " (" << xerces_ns << "::InputSource& i," << endl
             << error_handler << "& h," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << dom_auto_ptr << "< " << xerces_ns <<
            "::DOMDocument > d (" << endl
             << "::xsd::cxx::xml::dom::parse< " << char_type << " > (" << endl
             << "i, h, p, f";

          if (options.disable_multi_import ())
            os << " | ::xsd::cxx::xml::dom::no_muliple_imports";

          os << "));"
             << endl
             << "if (!d.get ())" << endl
             << "throw ::xsd::cxx::tree::parsing< " << char_type << " > ();"
             << endl
             << "return " << auto_ptr << "< " << type << " > (" << endl
             << fq_name (e, "parser") << " (" << endl
             << d << ", f | " << flags_type << "::own_dom, p));"
             << "}";


          os << auto_ptr << "< " << type << " >" << endl
             << name << " (" << xerces_ns << "::InputSource& i," << endl
             << xerces_ns << "::DOMErrorHandler& h," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << dom_auto_ptr << "< " << xerces_ns <<
            "::DOMDocument > d (" << endl
             << "::xsd::cxx::xml::dom::parse< " << char_type << " > (" << endl
             << "i, h, p, f";

          if (options.disable_multi_import ())
            os << " | ::xsd::cxx::xml::dom::no_muliple_imports";

          os << "));"
             << endl
             << "if (!d.get ())" << endl
             << "throw ::xsd::cxx::tree::parsing< " << char_type << " > ();"
             << endl
             << "return " << auto_ptr << "< " << type << " > (" << endl
             << fq_name (e, "parser") << " (" << endl
             << d << ", f | " << flags_type << "::own_dom, p));"
             << "}";


          // DOM.
          //

          bool fund (false);
          {
            IsFundamentalType test (fund);
            test.dispatch (t);
          }

          // const DOMDocument&
          //
          os << auto_ptr << "< " << type << " >" << endl
             << name << " (const " << xerces_ns << "::DOMDocument& doc," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "& p)"
             << "{"
             << "if (f & " << flags_type << "::keep_dom)"
             << "{"
             << dom_auto_ptr << "< " << xerces_ns <<
            "::DOMDocument > d (" << endl
             << "static_cast< " << xerces_ns <<
            "::DOMDocument* > (doc.cloneNode (true)));"
             << endl
             << "return " << auto_ptr << "< " << type << " > (" << endl
             << fq_name (e, "parser") << " (" << endl
             << d << ", f | " << flags_type << "::own_dom, p));"
             << "}"
             << "const " << xerces_ns << "::DOMElement& e (*doc.getDocumentElement ());"
             << "const " << qname_type << " n (" << endl
             << "::xsd::cxx::xml::dom::name< " << char_type << " > (e));"
             << endl;

          if (poly)
          {
            os << auto_ptr << "< ::xsd::cxx::tree::type > tmp (" << endl
               << "::xsd::cxx::tree::type_factory_map_instance< " <<
              poly_plate << ", " << char_type << " > ().create (" << endl
               << strlit (e.name ()) << "," << endl
               << strlit (e.namespace_().name ()) << "," << endl;

            if (abst)
              os << "0,";
            else
              os << "&::xsd::cxx::tree::factory_impl< " << type << " >,";

            os << endl
               << "true, true, e, n, f, 0));"
               << endl
               << "if (tmp.get () != 0)"
               << "{"
               << auto_ptr << "< " << type << " > r (" << endl
               << "dynamic_cast< " << type << "* > (tmp.get ()));"
               << endl
               << "if (r.get ())" << endl
               << "tmp.release ();"
               << "else" << endl
               << "throw ::xsd::cxx::tree::not_derived< " << char_type <<
              " > ();"
               << endl;
          }
          else
          {
            os << "if (n.name () == " << strlit (e.name ()) << " &&" << endl
               << "n.namespace_ () == " << strlit (e.namespace_().name ()) << ")"
               << "{";

            if (fund)
            {
              os << auto_ptr << "< " << type << " > r (" << endl
                 << "new " << type << " (" << endl
                 << "::xsd::cxx::tree::traits< " << type << ", " <<
                char_type;

              if (t.is_a<SemanticGraph::Fundamental::Double> ())
                os << ", ::xsd::cxx::tree::schema_type::double_";
              else if (t.is_a<SemanticGraph::Fundamental::Decimal> ())
                os << ", ::xsd::cxx::tree::schema_type::decimal";

              os << " >::create (" << endl
                 << "e, f, 0)));";
            }
            else
            {
              os << auto_ptr << "< " << type << " > r (" << endl
                 << "::xsd::cxx::tree::traits< " << type << ", " <<
                char_type << " >::create (" << endl
                 << "e, f, 0));";
            }
          }

          os << "return r;"
             << "}"
             << "throw ::xsd::cxx::tree::unexpected_element < " <<
            char_type << " > (" << endl
             << "n.name ()," << endl
             << "n.namespace_ ()," << endl
             << strlit (e.name ()) << "," << endl
             << strlit (e.namespace_().name ()) << ");"
             << "}";


          // dom::auto_ptr/unique_ptr<DOMDocument>
          //
          os << auto_ptr << "< " << type << " >" << endl
             << name << " (" << dom_auto_ptr << "< " << xerces_ns <<
            "::DOMDocument > d," << endl
             << flags_type << " f," << endl
             << "const " << properties_type << "&)"
             << "{"
             << dom_auto_ptr << "< " << xerces_ns <<
            "::DOMDocument > c (" << endl
             << "((f & " << flags_type << "::keep_dom) &&" << endl
             << "!(f & " << flags_type << "::own_dom))" << endl
             << "? static_cast< " << xerces_ns << "::DOMDocument* > (" <<
            "d->cloneNode (true))" << endl
             << ": 0);"
             << endl
             << xerces_ns << "::DOMDocument& doc (c.get () ? *c : *d);"
             << "const " << xerces_ns << "::DOMElement& e (" <<
            "*doc.getDocumentElement ());"
             << endl
             << "const " << qname_type << " n (" << endl
             << "::xsd::cxx::xml::dom::name< " << char_type << " > (e));"
             << endl
             << "if (f & " << flags_type << "::keep_dom)" << endl
             << "doc.setUserData (" << dom_node_key << "," << endl
             << "(c.get () ? &c : &d)," << endl
             << "0);"
             << endl;

          if (poly)
          {
            os << auto_ptr << "< ::xsd::cxx::tree::type > tmp (" << endl
               << "::xsd::cxx::tree::type_factory_map_instance< " <<
              poly_plate << ", " << char_type << " > ().create (" << endl
               << strlit (e.name ()) << "," << endl
               << strlit (e.namespace_().name ()) << "," << endl;

            if (abst)
              os << "0,";
            else
              os << "&::xsd::cxx::tree::factory_impl< " << type << " >,";

            os << endl
               << "true, true, e, n, f, 0));"
               << endl
               << "if (tmp.get () != 0)"
               << "{";
          }
          else
          {
            os << "if (n.name () == " << strlit (e.name ()) << " &&" << endl
               << "n.namespace_ () == " << strlit (e.namespace_().name ()) << ")"
               << "{";

            if (fund)
            {
              os << auto_ptr << "< " << type << " > r (" << endl
                 << "new " << type << " (" << endl
                 << "::xsd::cxx::tree::traits< " << type << ", " <<
                char_type;

              if (t.is_a<SemanticGraph::Fundamental::Double> ())
                os << ", ::xsd::cxx::tree::schema_type::double_";
              else if (t.is_a<SemanticGraph::Fundamental::Decimal> ())
                os << ", ::xsd::cxx::tree::schema_type::decimal";

              os << " >::create (" << endl
                 << "e, f, 0)));";
            }
            else
            {
              os << auto_ptr << "< " << type << " > r (" << endl
                 << "::xsd::cxx::tree::traits< " << type << ", " <<
                char_type << " >::create (" << endl
                 << "e, f, 0));";
            }
          }

          if (poly)
          {
            os << endl
               << auto_ptr << "< " << type << " > r (" << endl
               << "dynamic_cast< " << type << "* > (tmp.get ()));"
               << endl
               << "if (r.get ())" << endl
               << "tmp.release ();"
               << "else" << endl
               << "throw ::xsd::cxx::tree::not_derived< " << char_type <<
              " > ();"
               << endl;
          }

          os << "return r;"
             << "}"
             << "throw ::xsd::cxx::tree::unexpected_element < " <<
            char_type << " > (" << endl
             << "n.name ()," << endl
             << "n.namespace_ ()," << endl
             << strlit (e.name ()) << "," << endl
             << strlit (e.namespace_().name ()) << ");"
             << "}";
        }

      private:
        String
        type_name (Type& e)
        {
          std::wostringstream o;

          MemberTypeName type (*this, o);
          type.dispatch (e.type ());

          return o.str ();
        }
      };
    }

    void
    generate_parser_source (Context& ctx, size_t first, size_t last)
    {
      ctx.os << "#include <istream>" << endl
             << "#include <xsd/cxx/xml/sax/std-input-source.hxx>" << endl
             << "#include <xsd/cxx/tree/error-handler.hxx>" << endl
             << endl;

      Traversal::Schema schema;
      Sources sources;
      Traversal::Names names_ns, names;
      Namespace ns (ctx, first, last);
      ElementFunction element (ctx);

      schema >> sources >> schema;
      schema >> names_ns >> ns >> names >> element;

      schema.dispatch (ctx.schema_root);
    }
  }
}

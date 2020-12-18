// file      : xsd/cxx/tree/tree-source.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <map>
#include <list>

#include <libxsd-frontend/semantic-graph.hxx>
#include <libxsd-frontend/traversal.hxx>

#include <xsd/cxx/tree/tree-source.hxx>
#include <xsd/cxx/tree/default-value.hxx>

using namespace std;

namespace CXX
{
  namespace Tree
  {
    namespace
    {
      struct List: Traversal::List, Context
      {
        List (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& l)
        {
          String name (ename (l));

          // If renamed name is empty then we do not need to generate
          // anything for this type.
          //
          if (renamed_type (l, name) && !name)
            return;

          os << "// " << name << endl
             << "//" << endl
             << endl;

          if (!options.suppress_parsing ())
          {
            SemanticGraph::Type& item_type (l.argumented ().type ());
            String base (L"::xsd::cxx::tree::list< " +
                         item_type_name (item_type) + L", " + char_type);

            if (item_type.is_a<SemanticGraph::Fundamental::Double> ())
              base += L", ::xsd::cxx::tree::schema_type::double_";
            else if (item_type.is_a<SemanticGraph::Fundamental::Decimal> ())
              base += L", ::xsd::cxx::tree::schema_type::decimal";

            base += L" >";

            // c-tor (xercesc::DOMElement)
            //
            os << name << "::" << endl
               << name << " (const " << xerces_ns << "::DOMElement& e," << endl
               << flags_type << " f," << endl
               << container << "* c)" << endl
               << ": " << any_simple_type << " (e, f, c)," << endl
               << "  " << base << " (e, f, this)"
               << "{"
               << "}";

            // c-tor (xercesc::DOMAttr)
            //
            os << name << "::" << endl
               << name << " (const " << xerces_ns << "::DOMAttr& a," << endl
               << flags_type << " f," << endl
               << container << "* c)" << endl
               << ": " << any_simple_type << " (a, f, c)," << endl
               << "  " << base << " (a, f, this)"
               << "{"
               << "}";

            // c-tor (string const&, xercesc::DOMElement)
            //
            os << name << "::" << endl
               << name << " (const " << string_type << "& s," << endl
               << "const " << xerces_ns << "::DOMElement* e," << endl
               << flags_type << " f," << endl
               << container << "* c)" << endl
               << ": " << any_simple_type << " (s, e, f, c)," << endl
               << "  " << base << " (s, e, f, this)"
               << "{"
               << "}";
          }

          // _clone
          //
          os << name << "* " << name << "::" << endl
             << "_clone (" << flags_type << " f," << endl
             << container << "* c) const"
             << "{"
             << "return new class " << name << " (*this, f, c);"
             << "}";

          // d-tor
          //
          os << name << "::" << endl
             << "~" << name << " ()"
             << "{"
             << "}";

          // Register with type factory map.
          //
          if (polymorphic && polymorphic_p (l))
          {
            // Note that we are using the original type name.
            //
            String const& name (ename (l));

            // If this type is anonymous but substitutes, then it will
            // be registered as part of the substitution registration.
            //
            if (!anonymous_p (l) && !options.suppress_parsing ())
            {
              os << "static" << endl
                 << "const ::xsd::cxx::tree::type_factory_initializer< " <<
                poly_plate << ", " << char_type << ", " << name << " >" << endl
                 << "_xsd_" << name << "_type_factory_init (" << endl
                 << strlit (l.name ()) << "," << endl
                 << strlit (xml_ns_name (l)) << ");"
                 << endl;
            }

            if ((!anonymous_p (l) || anonymous_substitutes_p (l)) &&
                options.generate_comparison ())
            {
              os << "static" << endl
                 << "const ::xsd::cxx::tree::comparison_initializer< " <<
                poly_plate << ", " << char_type << ", " << name << " >" << endl
                 << "_xsd_" << name << "_comparison_init;"
                 << endl;
            }
          }
        }

      private:
        String
        item_type_name (SemanticGraph::Type& t)
        {
          std::wostringstream o;

          MemberTypeName type (*this, o);
          type.dispatch (t);

          return o.str ();
        }
      };


      struct Union: Traversal::Union, Context
      {
        Union (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& u)
        {
          String name (ename (u));

          // If renamed name is empty then we do not need to generate
          // anything for this type.
          //
          if (renamed_type (u, name) && !name)
            return;

          String const& base (xs_string_type);

          os << "// " << name << endl
             << "//" << endl
             << endl;

          if (!options.suppress_parsing ())
          {
            // c-tor (xercesc::DOMElement)
            //
            os << name << "::" << endl
               << name << " (const " << xerces_ns << "::DOMElement& e," << endl
               << flags_type << " f," << endl
               << container << "* c)" << endl
               << ": " << base << " (e, f, c)"
               << "{"
               << "}";

            // c-tor (xercesc::DOMAttr)
            //
            os << name << "::" << endl
               << name << " (const " << xerces_ns << "::DOMAttr& a," << endl
               << flags_type << " f," << endl
               << container << "* c)" << endl
               << ": " << base << " (a, f, c)"
               << "{"
               << "}";

            // c-tor (string const&, xercesc::DOMElement)
            //
            os << name << "::" << endl
               << name << " (const " << string_type << "& s," << endl
               << "const " << xerces_ns << "::DOMElement* e," << endl
               << flags_type << " f," << endl
               << container << "* c)" << endl
               << ": " << base << " (s, e, f, c)"
               << "{"
               << "}";
          }

          // _clone
          //
          os << name << "* " << name << "::" << endl
             << "_clone (" << flags_type << " f," << endl
             << container << "* c) const"
             << "{"
             << "return new class " << name << " (*this, f, c);"
             << "}";

          // Register with type factory map.
          //
          if (polymorphic && polymorphic_p (u))
          {
            // Note that we are using the original type name.
            //
            String const& name (ename (u));

            // If this type is anonymous but substitutes, then it will
            // be registered as part of the substitution registration.
            //
            if (!anonymous_p (u) && !options.suppress_parsing ())
            {
              os << "static" << endl
                 << "const ::xsd::cxx::tree::type_factory_initializer< " <<
                poly_plate << ", " << char_type << ", " << name << " >" << endl
                 << "_xsd_" << name << "_type_factory_init (" << endl
                 << strlit (u.name ()) << "," << endl
                 << strlit (xml_ns_name (u)) << ");"
                 << endl;
            }

            if ((!anonymous_p (u) || anonymous_substitutes_p (u)) &&
                options.generate_comparison ())
            {
              os << "static" << endl
                 << "const ::xsd::cxx::tree::comparison_initializer< " <<
                poly_plate << ", " << char_type << ", " << name << " >" << endl
                 << "_xsd_" << name << "_comparison_init;"
                 << endl;
            }
          }
        }
      };


      // Enumeration mapping.
      //

      struct EnumeratorLiteral: Traversal::Enumerator, Context
      {
        EnumeratorLiteral (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& e)
        {
          os << strlit (e.name ());
        }
      };


      //
      //
      struct LiteralInfo
      {
        LiteralInfo (String const& value, String const& name)
            : value_ (value), name_ (name)
        {
        }

        String value_;
        String name_;
      };

      bool
      operator< (LiteralInfo const& x, LiteralInfo const& y)
      {
        return x.value_ < y.value_;
      }

      typedef list<LiteralInfo> LiteralInfoList;


      // Populate LiteralInfoList
      //
      struct EnumeratorLiteralInfo: Traversal::Enumerator, Context

      {
        EnumeratorLiteralInfo (Context& c, LiteralInfoList& list)
            : Context (c), list_ (list)
        {
        }

        virtual void
        traverse (Type& e)
        {
          list_.push_back (LiteralInfo (e.name (), ename (e)));
        }

      private:
        LiteralInfoList& list_;
      };


      struct Enumeration: Traversal::Enumeration, Context
      {
        Enumeration (Context& c)
            : Context (c), enumerator_literal_ (c)
        {
          names_enumerator_literal_ >> enumerator_literal_;
        }

        virtual void
        traverse (Type& e)
        {
          String name (ename (e));

          // If renamed name is empty then we do not need to generate
          // anything for this type.
          //
          if (renamed_type (e, name) && !name)
            return;

          bool string_based (false);
          {
            IsStringBasedType t (string_based);
            t.dispatch (e);
          }

          SemanticGraph::Enumeration* be (0);
          bool enum_based (false);
          if (string_based)
          {
            IsEnumBasedType t (be);
            t.dispatch (e);

            enum_based = (be != 0);
          }

          String value;
          if (string_based)
            value = evalue (e);

          size_t enum_count (0);

          for (Type::NamesIterator i (e.names_begin ()), end (e.names_end ());
               i != end; ++i)
            ++enum_count;

          String base; // base type name
          {
            std::wostringstream o;

            BaseTypeName base_type (*this, o);
            Traversal::Inherits inherits_type (base_type);

            inherits (e, inherits_type);
            base = o.str ();
          }

          os << "// " << name << endl
             << "//" << endl
             << endl;

          if (!options.suppress_parsing ())
          {
            // c-tor (xercesc::DOMElement)
            //
            os << name << "::" << endl
               << name << " (const " << xerces_ns << "::DOMElement& e," << endl
               << flags_type << " f," << endl
               << container << "* c)" << endl
               << ": " << base << " (e, f, c)"
               << "{";

            if (string_based)
              os << "_xsd_" << name << "_convert ();";

            os << "}";


            // c-tor (xercesc::DOMAttr)
            //
            os << name << "::" << endl
               << name << " (const " << xerces_ns << "::DOMAttr& a," << endl
               << flags_type << " f," << endl
               << container << "* c)" << endl
               << ": " << base << " (a, f, c)"
               << "{";

            if (string_based)
            {
              os << "_xsd_" << name << "_convert ();";
            }

            os << "}";


            // c-tor (string const&, xercesc::DOMElement)
            //
            os << name << "::" << endl
               << name << " (const " << string_type << "& s," << endl
               << "const " << xerces_ns << "::DOMElement* e," << endl
               << flags_type << " f," << endl
               << container << "* c)" << endl
               << ": " << base << " (s, e, f, c)"
               << "{";

            if (string_based)
            {
              os << "_xsd_" << name << "_convert ();";
            }

            os << "}";
          }

          // _clone
          //
          os << name << "* " << name << "::" << endl
             << "_clone (" << flags_type << " f," << endl
             << container << "* c) const"
             << "{"
             << "return new class " << name << " (*this, f, c);"
             << "}";

          // convert
          //
          // @@ TODO: expected list
          //
          if (string_based)
          {
            String i_name (L"_xsd_" + name + L"_indexes_");

            os << name << "::" << value << " " <<
              name << "::" << endl
               << "_xsd_" << name << "_convert () const"
               << "{"
               << "::xsd::cxx::tree::enum_comparator< " << char_type <<
              " > c (_xsd_" << name << "_literals_);"
               << "const " << value << "* i (::std::lower_bound (" << endl
               << i_name << "," << endl
               << i_name << " + " << enum_count << "," << endl
               << "*this," << endl
               << "c));"
               << endl
               << "if (i == " << i_name << " + " << enum_count << " || " <<
              "_xsd_" << name << "_literals_[*i] != *this)"
               << "{"
               << "throw ::xsd::cxx::tree::unexpected_enumerator < " <<
              char_type << " > (*this);"
               << "}"
               << "return *i;"
               << "}";
          }

          // literals and indexes
          //
          if (string_based)
          {
            if (enum_based)
            {
              os << "const " << char_type << "* const* " << name << "::" << endl
                 << "_xsd_" << name << "_literals_ = " <<
                fq_name (*be) << "::_xsd_" << ename (*be) << "_literals_;"
                 << endl;
            }
            else
            {
              os << "const " << char_type << "* const " << name << "::" << endl
                 << "_xsd_" << name << "_literals_[" << enum_count << "] ="
                 << "{";

              names<Enumeration> (
                e, names_enumerator_literal_, 0, 0, 0, &Enumeration::comma);

              os << "};";
            }


            LiteralInfoList l;
            {
              EnumeratorLiteralInfo enumerator (*this, l);
              Traversal::Names names_enumerator (enumerator);
              names (e, names_enumerator);
            }

            l.sort ();

            os << "const " << name << "::" << value << " " <<
              name << "::" << endl
               << "_xsd_" << name << "_indexes_[" << enum_count << "] ="
               << "{";

            String fq_name (ns_scope + L"::" + name);

            for (LiteralInfoList::iterator
                   b (l.begin ()), i (b), end (l.end ()); i != end; ++i)
            {
              if (i != b)
                os << "," << endl;

              os << fq_name << "::" << i->name_;
            }

            os << "};";
          }

          // Register with type factory map.
          //
          if (polymorphic && polymorphic_p (e))
          {
            // Note that we are using the original type name.
            //
            String const& name (ename (e));

            // If this type is anonymous but substitutes, then it will
            // be registered as part of the substitution registration.
            //
            if (!anonymous_p (e) && !options.suppress_parsing ())
            {
              os << "static" << endl
                 << "const ::xsd::cxx::tree::type_factory_initializer< " <<
                poly_plate << ", " << char_type << ", " << name << " >" << endl
                 << "_xsd_" << name << "_type_factory_init (" << endl
                 << strlit (e.name ()) << "," << endl
                 << strlit (xml_ns_name (e)) << ");"
                 << endl;
            }

            if ((!anonymous_p (e) || anonymous_substitutes_p (e)) &&
                options.generate_comparison ())
            {
              os << "static" << endl
                 << "const ::xsd::cxx::tree::comparison_initializer< " <<
                poly_plate << ", " << char_type << ", " << name << " >" << endl
                 << "_xsd_" << name << "_comparison_init;"
                 << endl;
            }
          }
        }

        virtual void
        comma (Type&)
        {
          os << "," << endl;
        }

      private:
        Traversal::Names names_enumerator_literal_;
        EnumeratorLiteral enumerator_literal_;

      };

      //
      //
      struct Member: Traversal::Member, Context
      {
        Member (Context& c, String const& scope)
            : Context (c), scope_ (scope), init_value_ (c)
        {
        }

        virtual void
        traverse (Type& m)
        {
	  if (skip (m))
            return;

          // default_value
          //
          if (m.default_p ())
          {
            SemanticGraph::Type& t (m.type ());
            bool simple (true);

            if (m.is_a<SemanticGraph::Element> ())
            {
              IsSimpleType test (simple);
              test.dispatch (t);
            }

            if (simple)
            {
              bool lit (false);
              {
                IsLiteralValue test (lit);
                test.dispatch (t);
              }

              if (!lit)
              {
                InitKind::Kind kind (InitKind::simple);
                {
                  InitKind test (kind);
                  test.dispatch (t);
                }

                String const& member (edefault_value_member (m));

                String init_name;

                switch (kind)
                {
                case InitKind::data:
                  {
                    init_name = escape (L"_xsd_" + scope_ + member + L"data");
                    init_value_.data (init_name);
                    init_value_.dispatch (t, m.value ());
                    break;
                  }
                case InitKind::function:
                  {
                    init_name = escape (L"_xsd_" + scope_ + member + L"init");

                    os << "static " << scope_ << "::" << etype (m) << endl
                       << init_name << " ()"
                       << "{"
                       << scope_ << "::" << etype (m) << " r;"
                       << endl;

                    init_value_.dispatch (t, m.value ());

                    os << "return r;"
                       << "};";
                    break;
                  }
                case InitKind::simple:
                  break;
                }

                os << "const " << scope_ << "::" << etype (m) << " " <<
                  scope_ << "::" << member << " (" << endl;

                switch (kind)
                {
                case InitKind::data:
                  {
                    // Second dispatch.
                    //
                    init_value_.dispatch (t, m.value ());
                    break;
                  }
                case InitKind::function:
                  {
                    os << init_name << " ()";
                    break;
                  }
                case InitKind::simple:
                  {
                    init_value_.dispatch (t, m.value ());
                    break;
                  }
                }

                os << ");"
                   << endl;
              }
            }
          }
        }

      private:
        String scope_;
        InitValue init_value_;
      };


      struct Element: Traversal::Element, Context
      {
        Element (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& e)
        {
          if (skip (e))
            return;

          SemanticGraph::Complex& c (
            dynamic_cast<SemanticGraph::Complex&> (e.scope ()));

          String const& member (emember (e));

          String tr (etraits (e)); // traits type name
          String type (etype (e));

          SemanticGraph::Type& t (e.type ());

          bool fund (false);
          {
            IsFundamentalType traverser (fund);
            traverser.dispatch (t);
          }

          // Check if we need to handle xsi:type and substitution groups.
          // If this element's type is anonymous then we don't need to do
          // anything. Note that if the type is anonymous then it can't be
          // derived from which makes it impossible to substitute or
          // dynamically-type with xsi:type.
          //
          bool poly (polymorphic && polymorphic_p (t) && !anonymous_p (t));

          os << "// " << comment (e.name ()) << endl
             << "//" << endl;

          if (poly)
          {
            os << "{"
               << auto_ptr << "< ::xsd::cxx::tree::type > tmp (" << endl
               << "::xsd::cxx::tree::type_factory_map_instance< " <<
              poly_plate << ", " << char_type << " > ().create (" << endl
               << strlit (e.name ()) << "," << endl
               << (e.qualified_p ()
                   ? strlit (e.namespace_ ().name ())
                   : L + String ("\"\"")) << "," << endl;

            SemanticGraph::Complex* tc;
            if ((tc = dynamic_cast<SemanticGraph::Complex*> (&t)) != 0 &&
                tc->abstract_p ())
              os << "0,";
            else
              os << "&::xsd::cxx::tree::factory_impl< " << type << " >,";

            os << endl
               << (e.global_p () ? "true" : "false") << ", " <<
              (e.qualified_p () ? "true" : "false") << ", " <<
              "i, n, f, this));"
               << endl
               << "if (tmp.get () != 0)"
               << "{";
          }
          else
          {
            if (e.qualified_p () && e.namespace_ ().name ())
            {
              os << "if (n.name () == " << strlit (e.name ()) << " && " <<
                "n.namespace_ () == " << strlit (e.namespace_ ().name ()) << ")"
                 << "{";
            }
            else
            {
              os << "if (n.name () == " << strlit (e.name ()) << " && " <<
                "n.namespace_ ().empty ())"
                 << "{";
            }

            if (!fund)
            {
              os << auto_ptr << "< " << type << " > r (" << endl
                 << tr << "::create (i, f";

              if (t.is_a<SemanticGraph::AnyType> () &&
                  options.generate_any_type ())
                os << " | " << flags_type << "::extract_content";

              os << ", this));"
                 << endl;
            }
          }


          // Checks. Disabled at the moment since they make it impossible to
          // parse valid instances where the same element is used in both
          // base and derived types. See the cxx/tree/name-clash/inheritance
          // test for details.
          //
          //
          if (max (e) != 1)
          {
            // sequence
            //
          }
          else if (min (e) == 0)
          {
            // optional
            //
            os << "if (!this->" << member << ")"
               << "{";
          }
          else
          {
            // one
            //
            os << "if (!" << member << ".present ())"
               << "{";
          }


          if (poly || !fund)
          {
            if (poly)
            {
              // Cast to static type.
              //
              os << auto_ptr << "< " << type << " > r (" << endl
                 << "dynamic_cast< " << type << "* > (tmp.get ()));"
                 << endl
                 << "if (r.get ())" << endl
                 << "tmp.release ();"
                 << "else" << endl
                 << "throw ::xsd::cxx::tree::not_derived< " << char_type <<
                " > ();"
                 << endl;
            }

            char const* r (std >= cxx_version::cxx11 ? "::std::move (r)" : "r");

            if (max (e) != 1)
            {
              // sequence
              //
              os << "this->" << member << ".push_back (" << r << ");";
            }
            else if (min (e) == 0)
            {
              // optional
              //
              os << "this->" << member << ".set (" << r << ");";
            }
            else
            {
              // one
              //
              os << "this->" << member << ".set (" << r << ");";
            }
          }
          else
          {
            if (max (e) != 1)
            {
              // sequence
              //
              os << "this->" << member << ".push_back (" << tr <<
                "::create (i, f, this));";
            }
            else if (min (e) == 0)
            {
              // optional
              //
              os << "this->" << member << ".set (" << tr <<
                "::create (i, f, this));";
            }
            else
            {
              // one
              //
              os << "this->" << member << ".set (" << tr <<
                "::create (i, f, this));";
            }
          }

          // Capture order.
          //
          if (ordered_p (c))
          {
            SemanticGraph::Context& ctx (c.context ());

            String const& t (ctx.get<String> ("order-type"));
            String const& m (ctx.get<String> ("order-member"));

            os << "this->" << m << ".push_back (" << endl
               << t << " (" <<
              e.context ().get<String> ("ordered-id-name");

            // sequence
            //
            if (max (e) != 1)
              os << ", " << "this->" << member << ".size () - 1";

            os << "));";
          }

          os << "continue;";

          // End of check block.
          //
          if (max (e) != 1)
          {
            // sequence
            //
          }
          else if (min (e) == 0)
          {
            // optional
            //
            os << "}";
          }
          else
          {
            // one
            //
            os << "}";
          }

          os << "}"; // if block

          if (poly)
            os << "}";
        }
      };

      struct ElementTest: Traversal::Element, Context
      {
        ElementTest (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& e)
        {
          if (skip (e))
            return;

          if (max (e) == 1 && min (e) == 1)
          {
            // one
            //
            os << "if (!" << emember (e) << ".present ())"
               << "{"
               << "throw ::xsd::cxx::tree::expected_element< " <<
              char_type << " > (" << endl
               << strlit (e.name ()) << "," << endl
               << (e.qualified_p ()
                   ? strlit (e.namespace_ ().name ())
                   : L + String ("\"\"")) << ");"
               << "}";
          }
        }
      };

      struct Any: Traversal::Any, Context
      {
        Any (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& a)
        {
          String const& member (emember (a));

          SemanticGraph::Complex& c (
            dynamic_cast<SemanticGraph::Complex&> (a.scope ()));

          String const& ns (a.definition_namespace ().name ());
          String const& dom_doc (edom_document (c));

          os << "// " << ename (a) << endl
             << "//" << endl
             << "if (";

          for (SemanticGraph::Any::NamespaceIterator i (a.namespace_begin ()),
                 e (a.namespace_end ()); i != e;)
          {
            if (*i == L"##any")
            {
              os << "true";
            }
            else if (*i == L"##other")
            {
              if (ns)
              {
                // Note that here I assume that ##other does not include
                // unqualified names in a schema with target namespace.
                // This is not what the spec says but that seems to be
                // the consensus.
                //
                os << "(!n.namespace_ ().empty () && " <<
                  "n.namespace_ () != " << strlit (ns) << ")";
              }
              else
                os << "!n.namespace_ ().empty ()";
            }
            else if (*i == L"##local")
            {
              os << "n.namespace_ ().empty ()";
            }
            else if (*i == L"##targetNamespace")
            {
              os << "n.namespace_ () == " << strlit (ns);
            }
            else
            {
              os << "n.namespace_ () == " << strlit (*i);
            }

            if (++i != e)
              os << " ||" << endl;
          }

          os << ")"
             << "{";


          // Checks.
          //
          //
          if (max (a) != 1)
          {
            // sequence
            //
          }
          else if (min (a) == 0)
          {
            // optional
            //
            os << "if (!this->" << member << ")"
               << "{";
          }
          else
          {
            // one
            //
            os << "if (!" << member << ".present ())"
               << "{";
          }

          os << xerces_ns << "::DOMElement* r (" << endl
             << "static_cast< " << xerces_ns << "::DOMElement* > (" << endl
             << "this->" << dom_doc << " ().importNode (" << endl
             << "const_cast< " << xerces_ns << "::DOMElement* > (&i), true)));";

          if (max (a) != 1)
          {
            // sequence
            //
            os << "this->" << member << ".push_back (r);";
          }
          else if (min (a) == 0)
          {
            // optional
            //
            os << "this->" << member << ".set (r);";
          }
          else
          {
            // one
            //
            os << "this->" << member << ".set (r);";
          }

          // Capture order.
          //
          if (ordered_p (c))
          {
            SemanticGraph::Context& ctx (c.context ());

            String const& t (ctx.get<String> ("order-type"));
            String const& m (ctx.get<String> ("order-member"));

            os << "this->" << m << ".push_back (" << endl
               << t << " (" <<
              a.context ().get<String> ("ordered-id-name") << ", ";

            if (max (a) != 1)
              // sequence
              //
              os << "this->" << member << ".size () - 1";
            else
              // optional & one
              //
              os << "0";

            os << "));";
          }

          os << "continue;";

          // End of check block.
          //
          if (max (a) != 1)
          {
            // sequence
            //
          }
          else if (min (a) == 0)
          {
            // optional
            //
            os << "}";
          }
          else
          {
            // one
            //
            os << "}";
          }

          os << "}"; // if block
        }
      };

      struct AnyTest: Traversal::Any, Context
      {
        AnyTest (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& a)
        {
          if (max (a) == 1 && min (a) == 1)
          {
            // one
            //
            os << "if (!" << emember (a) << ".present ())"
               << "{"
               << "throw ::xsd::cxx::tree::expected_element< " <<
              char_type << " > (" << endl
               << L << "\"*\"," << endl
               << strlit (*a.namespace_begin ()) << ");"
               << "}";
          }
        }
      };

      struct Attribute: Traversal::Attribute, Context
      {
        Attribute (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& a)
        {
          String const& member (emember (a));

          String const& tr (etraits (a)); // traits type name

          if (a.qualified_p () && a.namespace_ ().name ())
          {
            os << "if (n.name () == " << strlit (a.name ()) << " && " <<
              "n.namespace_ () == " << strlit (a.namespace_ ().name ()) << ")"
               << "{";
          }
          else
          {
            os << "if (n.name () == " << strlit (a.name ()) << " && " <<
              "n.namespace_ ().empty ())"
               << "{";
          }

          os << "this->" << member << ".set (" << tr <<
            "::create (i, f, this));";

          os << "continue;"
             << "}";

        }
      };

      struct AnyAttribute: Traversal::AnyAttribute, Context
      {
        AnyAttribute (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& a)
        {
          String const& member (emember (a));

          String const& ns (a.definition_namespace ().name ());
          String const& dom_doc (
            edom_document (
              dynamic_cast<SemanticGraph::Complex&> (a.scope ())));

          os << "// " << ename (a) << endl
             << "//" << endl
             << "if (";

          // Note that we need to filter out namespaces for xmlns and
          // xsi.
          //
          for (SemanticGraph::Any::NamespaceIterator i (a.namespace_begin ()),
                 e (a.namespace_end ()); i != e;)
          {
            if (*i == L"##any")
            {
              os << "(n.namespace_ () != " <<
                "::xsd::cxx::xml::bits::xmlns_namespace< " << char_type <<
                " > () &&" << endl
                 << "n.namespace_ () != " <<
                "::xsd::cxx::xml::bits::xsi_namespace< " << char_type <<
                " > ())";
            }
            else if (*i == L"##other")
            {
              if (ns)
              {
                // Note that here I assume that ##other does not include
                // unqualified names in a schema with target namespace.
                // This is not what the spec says but that seems to be
                // the consensus.
                //
                os << "(!n.namespace_ ().empty () &&" << endl
                   << "n.namespace_ () != " << strlit (ns) << " &&" <<endl
                   << "n.namespace_ () != " <<
                  "::xsd::cxx::xml::bits::xmlns_namespace< " << char_type <<
                  " > () &&" << endl
                   << "n.namespace_ () != " <<
                  "::xsd::cxx::xml::bits::xsi_namespace< " << char_type <<
                  " > ())";
              }
              else
                os << "(!n.namespace_ ().empty () &&" << endl
                   << "n.namespace_ () != " <<
                  "::xsd::cxx::xml::bits::xmlns_namespace< " << char_type <<
                  " > () &&" << endl
                   << "n.namespace_ () != " <<
                  "::xsd::cxx::xml::bits::xsi_namespace< " << char_type <<
                  " > ())";
            }
            else if (*i == L"##local")
            {
              os << "n.namespace_ ().empty ()";
            }
            else if (*i == L"##targetNamespace")
            {
              os << "n.namespace_ () == " << strlit (ns);
            }
            else
            {
              os << "n.namespace_ () == " << strlit (*i);
            }

            if (++i != e)
              os << " ||" << endl;
          }

          os << ")"
             << "{"
             << xerces_ns << "::DOMAttr* r (" << endl
             << "static_cast< " << xerces_ns << "::DOMAttr* > (" << endl
             << "this->" << dom_doc << " ().importNode (" << endl
             << "const_cast< " << xerces_ns << "::DOMAttr* > (&i), true)));"
             << "this->" << member << " .insert (r);"
             << "continue;"
             << "}";
        }
      };


      struct AttributeTest: Traversal::Attribute, Context
      {
        AttributeTest (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& a)
        {
          String const& member (emember (a));

          if (!a.optional_p () || a.default_p ())
          {
            os << "if (!" << member << ".present ())"
               << "{";

            if (a.default_p ())
            {
              os << "this->" << member << ".set (" <<
                edefault_value (a) << " ());";
            }
            else
              os << "throw ::xsd::cxx::tree::expected_attribute< " <<
                char_type << " > (" << endl
                 << strlit (a.name ()) << "," << endl
                 << (a.qualified_p ()
                     ? strlit (a.namespace_ ().name ())
                     : L + String ("\"\"")) << ");";

            os << "}";
          }
        }
      };


      //
      //
      struct CtorBase: Traversal::Complex,
                       Traversal::Enumeration,
                       Traversal::Type,
                       Context
      {
        // If base_arg is empty then no base argument is generated.
        //
        CtorBase (Context& c, CtorArgType at, String const& base_arg)
            : Context (c), args_ (c, at, base_arg)
        {
        }

        virtual void
        traverse (SemanticGraph::Type&)
        {
          if (args_.base_arg_)
            os << args_.base_arg_;
        }

        virtual void
        traverse (SemanticGraph::Enumeration&)
        {
          if (args_.base_arg_)
            os << args_.base_arg_;
        }

        void
        traverse (SemanticGraph::Complex& c)
        {
          args_.traverse (c);
        }

      private:
        // No need to traverse AnyAttribute since it is always mapped
        // to a sequence.
        //
        struct Args: Traversal::Complex,
                     Traversal::Enumeration,
                     Traversal::Type,
                     Traversal::Any,
                     Traversal::Element,
                     Traversal::Attribute,
                     Context
        {
          Args (Context& c, CtorArgType at, String const& base_arg)
              : Context (c),
                arg_type_ (at), base_arg_ (base_arg), first_ (true)
          {
            *this >> inherits_ >> *this;
            *this >> names_ >> *this;
          }

          virtual void
          traverse (SemanticGraph::Type&)
          {
            if (base_arg_)
              os << comma () << base_arg_;
          }

          virtual void
          traverse (SemanticGraph::Enumeration&)
          {
            if (base_arg_)
              os << comma () << base_arg_;
          }

          virtual void
          traverse (SemanticGraph::Any& a)
          {
            if (!options.generate_wildcard ())
              return;

            if (min (a) == 1 && max (a) == 1)
            {
              // one
              //
              os << comma () << ename (a);
            }
          }

          virtual void
          traverse (SemanticGraph::Element& e)
          {
            if (!skip (e) && min (e) == 1 && max (e) == 1)
            {
              // one
              //
              bool move (false);

              if (std >= cxx_version::cxx11)
              {
                switch (arg_type_)
                {
                case CtorArgType::complex_auto_ptr:
                  {
                    bool simple (true);
                    IsSimpleType t (simple);
                    t.dispatch (e.type ());
                    move = !simple;
                    break;
                  }
                case CtorArgType::poly_auto_ptr:
                  {
                    move = polymorphic && polymorphic_p (e.type ());
                    break;
                  }
                case CtorArgType::type:
                  break;
                }
              }

              os << comma () << (move ? "std::move (" : "") << ename (e) <<
                (move ? ")" : "");
            }
          }

          virtual void
          traverse (SemanticGraph::Attribute& a)
          {
            // Note that we are not including attributes with default
            // or required fixed values here.
            //
            if (min (a) == 1 && !a.fixed_p ())
            {
              // one
              //
              os << comma () << ename (a);
            }
          }

          using Complex::traverse;

        private:
          String
          comma ()
          {
            bool tmp (first_);
            first_ = false;
            return tmp ? "" : ",\n";
          }

        public:
          CtorArgType arg_type_;
          String base_arg_;

        private:
          bool first_;

          Traversal::Inherits inherits_;
          Traversal::Names names_;
        };

        Args args_;
      };


      struct CtorMember: Traversal::Element,
                         Traversal::Attribute,
                         Context
      {
        CtorMember (Context& c, CtorArgType at)
            : Context (c), arg_type_ (at)
        {
        }

        virtual void
        traverse (SemanticGraph::Element& e)
        {
          if (skip (e))
            return;

          String const& member (emember (e));

          if (max (e) != 1)
          {
            // sequence
            //
            os << "," << endl
               << "  " << member << " (this)";
          }
          else if (min (e) == 0)
          {
            // optional
            //
            os << "," << endl
               << "  " << member << " (this)";
          }
          else
          {
            // one
            //
            bool move (false);

            if (std >= cxx_version::cxx11)
            {
              switch (arg_type_)
              {
              case CtorArgType::complex_auto_ptr:
                {
                  bool simple (true);
                  IsSimpleType t (simple);
                  t.dispatch (e.type ());
                  move = !simple;
                  break;
                }
              case CtorArgType::poly_auto_ptr:
                {
                  move = polymorphic && polymorphic_p (e.type ());
                  break;
                }
              case CtorArgType::type:
                break;
              }
            }

            os << "," << endl
               << "  " << member << " (" << (move ? "std::move (" : "") <<
              ename (e) << (move ? ")" : "") << ", this)";
          }
        }

        virtual void
        traverse (SemanticGraph::Attribute& a)
        {
          String const& member (emember (a));

          bool def (a.default_p ());

          if (min (a) == 0 && !def)
          {
            // optional
            //
            os << "," << endl
               << "  " << member << " (this)";
          }
          else
          {
            // one
            //

            if (def)
            {
              // This is an attribute with default or fixed value. We are
              // going to initialize it to its default value.
              //
              os << "," << endl
                 << "  " << member << " (" <<
                edefault_value (a) << " (), this)";
            }
            else
            {
              os << "," << endl
                 << "  " << member << " (" << ename (a) << ", this)";
            }
          }
        }

      private:
        CtorArgType arg_type_;
      };

      struct CtorAny: Traversal::Any,
                      Traversal::AnyAttribute,
                      Context
      {
        CtorAny (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (SemanticGraph::Any& a)
        {
          String const& member (emember (a));
          String const& dom_doc (
            edom_document (
              dynamic_cast<SemanticGraph::Complex&> (a.scope ())));

          if (max (a) != 1)
          {
            // sequence
            //
            os << "," << endl
               << "  " << member << " (this->" << dom_doc << " ())";
          }
          else if (min (a) == 0)
          {
            // optional
            //
            os << "," << endl
               << "  " << member << " (this->" << dom_doc << " ())";
          }
          else
          {
            // one
            //
            os << "," << endl
               << "  " << member << " (" << ename (a) << ", this->" <<
              dom_doc << " ())";
          }
        }

        virtual void
        traverse (SemanticGraph::AnyAttribute& a)
        {
          String const& dom_doc (
            edom_document (
              dynamic_cast<SemanticGraph::Complex&> (a.scope ())));

          os << "," << endl
             << "  " << emember (a) << " (this->" << dom_doc << " ())";
        }
      };


      struct CopyMember: Traversal::Member, Context
      {
        CopyMember (Context& c, String const& arg_name_)
            : Context (c), arg_name (arg_name_)
        {
        }

        virtual void
        traverse (SemanticGraph::Member& m)
        {
          if (skip (m))
            return;

          String const& member (emember (m));

          os << "," << endl
             << "  " << member << " (" <<
            arg_name << "." << member << ", f, this)";
        }

      private:
        String arg_name;
      };

      struct CopyAny: Traversal::Any,
                      Traversal::AnyAttribute,
                      Context
      {
        CopyAny (Context& c, String const& arg_name_)
            : Context (c), arg_name (arg_name_)
        {
        }

        virtual void
        traverse (SemanticGraph::Any& a)
        {
          String const& member (emember (a));
          String const& dom_doc (
            edom_document (
              dynamic_cast<SemanticGraph::Complex&> (a.scope ())));

          os << "," << endl
             << "  " << member << " (" <<
            arg_name << "." << member << ", this->" << dom_doc << " ())";
        }

        virtual void
        traverse (SemanticGraph::AnyAttribute& a)
        {
          String const& member (emember (a));
          String const& dom_doc (
            edom_document (
              dynamic_cast<SemanticGraph::Complex&> (a.scope ())));

          os << "," << endl
             << "  " << member << " (" <<
            arg_name << "." << member << ", this->" << dom_doc << " ())";
        }

      private:
        String arg_name;
      };

      struct AssignMember: Traversal::Member, Context
      {
        AssignMember (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (SemanticGraph::Member& m)
        {
          if (skip (m))
            return;

          String const& member (emember (m));
          os << "this->" << member << " = x." << member << ";";
        }
      };

      struct AssignAny: Traversal::Any,
                        Traversal::AnyAttribute,
                        Context
      {
        AssignAny (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (SemanticGraph::Any& a)
        {
          String const& member (emember (a));
          os << "this->" << member << " = x." << member << ";";
        }

        virtual void
        traverse (SemanticGraph::AnyAttribute& a)
        {
          String const& member (emember (a));
          os << "this->" << member << " = x." << member << ";";
        }
      };


      // Element parsing c-tor initializers.
      //
      struct ElementCtorMember: Traversal::Member, Context
      {
        ElementCtorMember (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& m)
        {
          if (skip (m))
            return;

          String const& member (emember (m));

          os << "," << endl
             << "  " << member << " (this)";
        }
      };

      struct ElementCtorAny: Traversal::Any,
                             Traversal::AnyAttribute,
                             Context
      {
        ElementCtorAny (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (SemanticGraph::Any& a)
        {
          String const& member (emember (a));
          String const& dom_doc (
            edom_document (
              dynamic_cast<SemanticGraph::Complex&> (a.scope ())));

          os << "," << endl
             << "  " << member << " (this->" << dom_doc << " ())";
        }

        virtual void
        traverse (SemanticGraph::AnyAttribute& a)
        {
          String const& member (emember (a));
          String const& dom_doc (
            edom_document (
              dynamic_cast<SemanticGraph::Complex&> (a.scope ())));

          os << "," << endl
             << "  " << member << " (this->" << dom_doc << " ())";
        }
      };


      // Default c-tor member initializer.
      //
      struct DefaultCtorMemberInit: Traversal::Element,
                                    Traversal::Attribute,
                                    Context
      {
        DefaultCtorMemberInit (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (SemanticGraph::Element& e)
        {
          if (skip (e))
            return;

          String const& member (emember (e));

          os << "," << endl
             << "  " << member << " (this)";
        }

        virtual void
        traverse (SemanticGraph::Attribute& a)
        {
          String const& member (emember (a));

          if (a.default_p ())
          {
            // This is an attribute with default or fixed value. We are
            // going to initialize it to its default value.
            //
            os << "," << endl
               << "  " << member << " (" <<
              edefault_value (a) << " (), this)";
          }
          else
            os << "," << endl
               << "  " << member << " (this)";
        }
      };

      struct DefaultCtorAnyInit: Traversal::Any,
                                 Traversal::AnyAttribute,
                                 Context
      {
        DefaultCtorAnyInit (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (SemanticGraph::Any& a)
        {
          String const& member (emember (a));
          String const& dom_doc (
            edom_document (
              dynamic_cast<SemanticGraph::Complex&> (a.scope ())));

          os << "," << endl
             << "  " << member << " (this->" << dom_doc << " ())";
        }

        virtual void
        traverse (SemanticGraph::AnyAttribute& a)
        {
          String const& member (emember (a));
          String const& dom_doc (
            edom_document (
              dynamic_cast<SemanticGraph::Complex&> (a.scope ())));

          os << "," << endl
             << "  " << member << " (this->" << dom_doc << " ())";
        }
      };

      // Test whether the base has comparison operators.
      //
      struct HasComparisonOperator: Traversal::Fundamental::Type,
                                    Traversal::List,
                                    Traversal::Union,
                                    Traversal::Complex,
                                    Traversal::Enumeration,
                                    Traversal::Member,
                                    Traversal::Any,
                                    Traversal::AnyAttribute,
                                    Context
      {
        // generate should initially be false.
        //
        HasComparisonOperator (Context& c, bool& generate)
            : Context (c), generate_ (generate)
        {
          *this >> inherits_ >> *this;
          *this >> names_ >> *this;
        }

        virtual void
        traverse (SemanticGraph::Fundamental::Type&)
        {
          // All built-in types are comparable.
          generate_ = true;
        }

        virtual void
        traverse (SemanticGraph::List&)
        {
          generate_ = true;
        }

        virtual void
        traverse (SemanticGraph::Union&)
        {
          generate_ = true;
        }

        virtual void
        traverse (SemanticGraph::Enumeration& e)
        {
          Traversal::Enumeration::inherits (e);
        }

        virtual void
        traverse (SemanticGraph::Complex& c)
        {
          Complex::names (c);

          if (!generate_)
            Complex::inherits (c);
        }

        virtual void
        traverse (SemanticGraph::Member& m)
        {
          if (!skip (m))
            generate_ = true;
        }

        virtual void
        traverse (SemanticGraph::Any&)
        {
          if (options.generate_wildcard ())
            generate_ = true;
        }

        virtual void
        traverse (SemanticGraph::AnyAttribute&)
        {
          if (options.generate_wildcard ())
            generate_ = true;
        }

      private:
        bool& generate_;

        Traversal::Inherits inherits_;
        Traversal::Names names_;
      };

      //
      //
      struct MemberComparison: Traversal::Element,
                               Traversal::Attribute,
                               Context
      {
        MemberComparison (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (SemanticGraph::Element& e)
        {
          if (skip (e))
            return;

          String const& aname (eaname (e));

          // Check if we need to handle xsi:type and substitution groups.
          // If this element's type is anonymous then we don't need to do
          // anything. Note that if the type is anonymous then it can't be
          // derived from which makes it impossible to substitute or
          // dynamically-type with xsi:type.
          //
          SemanticGraph::Type& t (e.type ());
          bool poly (polymorphic && polymorphic_p (t) && !anonymous_p (t));

          if (!poly)
          {
            os << "if (!(x." << aname << " () == y." << aname << " ()))" << endl
               << "return false;"
               << endl;
          }
          else
          {
            os << "{"
               << "::xsd::cxx::tree::comparison_map< " << char_type
               << " >& cm (" << endl
               << "::xsd::cxx::tree::comparison_map_instance< " <<
              poly_plate << ", " << char_type << " > ());"
               << endl;

            if (max (e) != 1)
            {
              // sequence
              //
              String const& scope (ename (e.scope ()));

              os << scope << "::" << econtainer (e) <<
                " a (x." << aname << " ()), b (y." << aname << " ());"
                 << endl;

              os << "if (a.size () != b.size ())" << endl
                 << "return false;"
                 << endl;

              os << "for (" << scope << "::" << econst_iterator (e) << endl
                 << "ai (a.begin ()), bi (b.begin ()), " <<
                "ae (a.end ()), be (b.end ());" << endl
                 << "ai != ae; ++ai, ++bi)"
                 << "{"
                 << "if (!cm.compare (*ai, *bi))" << endl
                 << "return false;"
                 << "}";
            }
            else if (min (e) == 0)
            {
              // optional
              //
              String const& scope (ename (e.scope ()));

              os << scope << "::" << econtainer (e) <<
                " a (x." << aname << " ()), b (y." << aname << " ());"
                 << endl;

              os << "if (!a || !b)"
                 << "{"
                 << "if (a.present () != b.present ())" << endl
                 << "return false;"
                 << "}"
                 << "else"
                 << "{"
                 << "if (!cm.compare (*a, *b))" << endl
                 << "return false;"
                 << "}";
            }
            else
            {
              // one
              //
              os << "if (!cm.compare (x." << aname << " (), y." <<
                aname << " ()))" << endl
                 << "return false;";
            }

            os << "}";
          }
        }

        virtual void
        traverse (SemanticGraph::Attribute& a)
        {
          String const& aname (eaname (a));

          os << "if (!(x." << aname << " () == y." << aname << " ()))" << endl
             << "return false;"
             << endl;
        }
      };

      struct AnyComparison: Traversal::Any,
                            Traversal::AnyAttribute,
                            Context
      {
        AnyComparison (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (SemanticGraph::Any& a)
        {
          String const& aname (eaname (a));

          if (max (a) == 1 && min (a) == 1)
            os << "if (!x." << aname << " ().isEqualNode (&y." <<
              aname << " ()))";
          else
            os << "if (!(x." << aname << " () == y." << aname << " ()))";

          os << endl
             << "return false;"
             << endl;
        }

        virtual void
        traverse (SemanticGraph::AnyAttribute& a)
        {
          String const& aname (eaname (a));

          os << "if (!(x." << aname << " () == y." << aname << " ()))" << endl
             << "return false;"
             << endl;
        }
      };

      // Check whether a type has a parse() function (i.e., has any
      // members, recursively).
      //
      struct HasParseFunction: Traversal::Complex,
                               Traversal::Element,
                               Traversal::Any,
                               Traversal::Attribute,
                               Traversal::AnyAttribute,
                               Context
      {
        HasParseFunction (Context& c, bool& has_el, bool& has_at)
            : Context (c), has_el_ (has_el), has_at_ (has_at)
        {
          *this >> names_ >> *this;
          *this >> inherits_ >> *this;
        }

        virtual void
        traverse (SemanticGraph::Complex& c)
        {
          if (mixed_p (c) && !c.context ().count ("mixed-in-base"))
            has_el_ = true;

          names (c);

          if (!(has_el_ && has_at_))
            inherits (c);
        }

        virtual void
        traverse (SemanticGraph::Element&)
        {
          has_el_ = true;
        }

        virtual void
        traverse (SemanticGraph::Any&)
        {
          has_el_ = true;
        }

        virtual void
        traverse (SemanticGraph::Attribute&)
        {
          has_at_ = true;
        }

        virtual void
        traverse (SemanticGraph::AnyAttribute&)
        {
          if (options.generate_wildcard ())
            has_at_ = true;
        }

      private:
        bool& has_el_;
        bool& has_at_;

        Traversal::Names names_;
        Traversal::Inherits inherits_;
      };

      //
      //
      struct FacetArray: Traversal::Complex, Context
      {
        FacetArray (Context& c)
            : Context (c)
        {
        }

        virtual void
        traverse (Type& c)
        {
          Facets f;
          FacetCollector col (f);
          col.traverse (c);

          for (Facets::const_iterator i (f.begin ()); i != f.end (); ++i)
          {
            if (i->first == L"fractionDigits")
              os << "{::xsd::cxx::tree::facet::fraction_digits, " <<
                i->second << "UL}," << endl;
            else if (i->first == L"totalDigits")
              os << "{::xsd::cxx::tree::facet::total_digits, " <<
                i->second << "UL}," << endl;
          }
        }

      private:
        typedef map<String, String> Facets;

        struct FacetCollector: Traversal::Complex
        {
          FacetCollector (Facets& facets)
              : facets_ (facets)
          {
            *this >> inherits_ >> *this;
          }

          virtual void
          traverse (Type& c)
          {
            if (c.inherits_p ())
            {
              // First collect our base so that we can override its
              // facets.
              //
              inherits (c);

              using SemanticGraph::Restricts;

              if (Restricts* r = dynamic_cast<Restricts*> (&c.inherits ()))
              {
                if (!r->facet_empty ())
                {
                  Restricts::FacetIterator i (r->facet_find ("totalDigits"));

                  if (i != r->facet_end ())
                    facets_[i->first] = i->second;

                  i = r->facet_find ("fractionDigits");

                  if (i != r->facet_end ())
                    facets_[i->first] = i->second;
                }
              }
            }
          }

        private:
          Traversal::Inherits inherits_;
          Facets& facets_;
        };
      };

      //
      //
      struct Complex: Traversal::Complex, Context
      {
        Complex (Context& c)
            : Context (c),
              member_name_ (c),
              any_ (c),
              element_ (c),
              any_test_ (c),
              element_test_ (c),
              attribute_ (c),
              attribute_test_ (c),
              any_attribute_ (c),
              default_ctor_any_init_ (c),
              default_ctor_member_init_ (c),
              ctor_any_ (c),
              ctor_member_ (c, CtorArgType::type),
              element_ctor_any_ (c),
              element_ctor_member_ (c),
              assign_any_ (c),
              assign_member_ (c),
              comparison_any_ (c),
              comparison_member_ (c),
              facet_array_ (c)
        {
          bool gen_wildcard (options.generate_wildcard ());

          inherits_member_ >> member_name_;

          names_element_ >> element_;
          if (gen_wildcard)
            names_element_ >> any_;

          names_element_test_ >> element_test_;
          if (gen_wildcard)
            names_element_test_ >> any_test_;

          names_attribute_ >> attribute_;
          names_attribute_test_ >> attribute_test_;
          names_any_attribute_ >> any_attribute_;

          default_ctor_init_names_ >> default_ctor_member_init_;
          if (gen_wildcard)
            default_ctor_init_names_ >> default_ctor_any_init_;

          ctor_names_ >> ctor_member_;
          if (gen_wildcard)
            ctor_names_ >> ctor_any_;

          element_ctor_names_ >> element_ctor_member_;
          if (gen_wildcard)
            element_ctor_names_ >> element_ctor_any_;

          assign_names_ >> assign_member_;
          if (gen_wildcard)
            assign_names_ >> assign_any_;

          comparison_names_ >> comparison_member_;
          if (gen_wildcard)
            comparison_names_ >> comparison_any_;
        }


        virtual void
        traverse (Type& c)
        {
          bool gen_wildcard (options.generate_wildcard ());

          String name (ename (c));

          // If renamed name is empty then we do not need to generate
          // anything for this type.
          //
          bool renamed (renamed_type (c, name));
          if (renamed && !name)
            return;

          SemanticGraph::Context& ctx (c.context ());

          bool mixed (mixed_p (c) && !ctx.count ("mixed-in-base"));
          bool ordered (ordered_p (c) && !ctx.count ("order-in-base"));

          bool string_based (false);
          {
            IsStringBasedType t (string_based);
            t.dispatch (c);
          }

          SemanticGraph::Enumeration* enum_base (0);
          {
            IsEnumBasedType t (enum_base);
            t.dispatch (c);
          }

          bool facets (false);
          String base; // base type name
          if (c.inherits_p ())
          {
            // Get base name.
            //
            std::wostringstream o;

            BaseTypeName base_type (*this, o);
            Traversal::Inherits inherits_type (base_type);

            // Cannot use inherits_none here because need the
            // result in a string.
            //
            inherits (c, inherits_type);

            base = o.str ();

            // See if we have any facets that we need to handle.
            //
            using SemanticGraph::Restricts;
            using SemanticGraph::Fundamental::Decimal;

            if (Restricts* r = dynamic_cast<Restricts*> (&c.inherits ()))
            {
              if (!r->facet_empty () &&
                  (r->facet_find ("fractionDigits") != r->facet_end () ||
                   r->facet_find ("totalDigits") != r->facet_end ()) &&
                  ultimate_base (c).is_a<Decimal> ())
                facets = true;
            }
          }
          else
            base = any_type;

          os << "// " << name << endl
             << "//" << endl
             << endl;

          //
          //
          {
            Member member (*this, name);
            Traversal::Names names_member (member);
            names (c, names_member);
          }

          // facets
          //
          if (facets)
          {
            os << "static const ::xsd::cxx::tree::facet _xsd_" << name <<
              "_facet_table[] = "
               << "{";

            facet_array_.traverse (c);

            os << "{::xsd::cxx::tree::facet::none, 0UL}"
               << "};";
          }

          // c-tors
          //
          bool generate_no_base_ctor (false);
          {
            GenerateWithoutBaseCtor t (generate_no_base_ctor);
            t.traverse (c);
          }

          bool has_complex_non_op_args (false);
          bool has_poly_non_op_args (false);
          bool complex_poly_args_clash (true);
          {
            HasComplexPolyNonOptArgs t (*this, true,
                                        has_complex_non_op_args,
                                        has_poly_non_op_args,
                                        complex_poly_args_clash);
            t.traverse (c);
          }

          // default c-tor
          //
          if (options.generate_default_ctor ())
          {
            bool generate (false);
            {
              GenerateDefaultCtor t (*this, generate, generate_no_base_ctor);
              t.traverse (c);
            }

            if (generate)
            {
              os << name << "::" << endl
                 << name << " ()" << endl
                 << ": " << base << " ()";

              if (edom_document_member_p (c))
              {
                os << "," << endl
                   << "  " << edom_document_member (c) << " (" <<
                  "::xsd::cxx::xml::dom::create_document< " << char_type <<
                  " > ())";
              }

              if (mixed)
              {
                os << "," << endl
                   << "  " << ctx.get<String> ("mixed-member") << " (this)";
              }

              names (c, default_ctor_init_names_);

              os << "{";
              if (facets)
                os << "this->_facet_table (_xsd_" << name << "_facet_table);";
              os << "}";
            }
          }

          // c-tor (base, all-non-optional-members)
          //
          if (options.generate_from_base_ctor ())
          {
            bool generate (false);
            {
              GenerateFromBaseCtor t (*this, generate);
              t.traverse (c);
            }

            if (generate)
            {
              bool has_complex_non_op_args (false);
              bool has_poly_non_op_args (false);
              bool complex_poly_args_clash (true);
              {
                HasComplexPolyNonOptArgs t (*this, false,
                                            has_complex_non_op_args,
                                            has_poly_non_op_args,
                                            complex_poly_args_clash);
                t.traverse (c);
              }

              String base_arg (
                L"_xsd_" + ename (c.inherits ().base ()) + L"_base");

              os << name << "::" << endl
                 << name << " (const ";
              inherits (c, inherits_member_);
              os << "& " << base_arg;
              {
                FromBaseCtorArg args (*this, CtorArgType::type, true);
                Traversal::Names args_names (args);
                names (c, args_names);
              }
              os << ")" << endl
                 << ": " << base << " (" << base_arg << ")";

              if (edom_document_member_p (c))
              {
                os << "," << endl
                   << "  " << edom_document_member (c) << " (" <<
                  "::xsd::cxx::xml::dom::create_document< " << char_type <<
                  " > ())";
              }

              if (mixed)
              {
                os << "," << endl
                   << "  " << ctx.get<String> ("mixed-member") << " (this)";
              }

              names (c, ctor_names_);

              os << "{";
              if (facets)
                os << "this->_facet_table (_xsd_" << name << "_facet_table);";
              os << "}";

              // If we have any complex arguments in the previous c-tor
              // then also generate the auto_ptr version.
              //
              if (has_complex_non_op_args)
              {
                CtorArgType const at (CtorArgType::complex_auto_ptr);

                os << name << "::" << endl
                   << name << " (const ";
                inherits (c, inherits_member_);
                os << "& " << base_arg;
                {
                  FromBaseCtorArg args (*this, at, true);
                  Traversal::Names args_names (args);
                  names (c, args_names);
                }
                os << ")" << endl
                   << ": " << base << " (" << base_arg << ")";

                if (edom_document_member_p (c))
                {
                  os << "," << endl
                     << "  " << edom_document_member (c) << " (" <<
                    "::xsd::cxx::xml::dom::create_document< " << char_type <<
                    " > ())";
                }

                if (mixed)
                {
                  os << "," << endl
                     << "  " << ctx.get<String> ("mixed-member") << " (this)";
                }

                {
                  CtorMember t (*this, at);
                  Traversal::Names n (t);

                  if (gen_wildcard)
                    n >> ctor_any_;

                  names (c, n);
                }

                os << "{";
                if (facets)
                  os << "this->_facet_table (_xsd_" << name << "_facet_table);";
                os << "}";
              }

              // If we are generating polymorphic code then we also need to
              // provide auto_ptr version for every polymorphic type.
              //
              if (polymorphic &&
                  has_poly_non_op_args && !complex_poly_args_clash)
              {
                CtorArgType const at (CtorArgType::poly_auto_ptr);

                os << name << "::" << endl
                   << name << " (const ";
                inherits (c, inherits_member_);
                os << "& " << base_arg;
                {
                  FromBaseCtorArg args (*this, at, true);
                  Traversal::Names args_names (args);
                  names (c, args_names);
                }
                os << ")" << endl
                   << ": " << base << " (" << base_arg << ")";

                if (edom_document_member_p (c))
                {
                  os << "," << endl
                     << "  " << edom_document_member (c) << " (" <<
                    "::xsd::cxx::xml::dom::create_document< " << char_type <<
                    " > ())";
                }

                if (mixed)
                {
                  os << "," << endl
                     << "  " << ctx.get<String> ("mixed-member") << " (this)";
                }

                {
                  CtorMember t (*this, at);
                  Traversal::Names n (t);

                  if (gen_wildcard)
                    n >> ctor_any_;

                  names (c, n);
                }

                os << "{";
                if (facets)
                  os << "this->_facet_table (_xsd_" << name << "_facet_table);";
                os << "}";
              }
            }
          }

          // c-tor (all-non-optional-members)
          //
          if (generate_no_base_ctor)
          {
            CtorArgType const at (CtorArgType::type);

            os << name << "::" << endl
               << name << " (";
            {
              CtorArgsWithoutBase ctor_args (*this, at, true, true);
              ctor_args.dispatch (c);
            }
            os << ")" << endl
               << ": " << base << " (";
            {
              CtorBase base (*this, at, "");
              Traversal::Inherits inherits_base (base);

              inherits (c, inherits_base);
            }
            os << ")";

            if (edom_document_member_p (c))
            {
              os << "," << endl
                 << "  " << edom_document_member (c) << " (" <<
                "::xsd::cxx::xml::dom::create_document< " << char_type <<
                " > ())";
            }

            if (mixed)
            {
              os << "," << endl
                 << "  " << ctx.get<String> ("mixed-member") << " (this)";
            }

            names (c, ctor_names_);

            os << "{";
            if (facets)
              os << "this->_facet_table (_xsd_" << name << "_facet_table);";
            os << "}";

            // If we have any complex arguments in the previous c-tor
            // then also generate the auto_ptr version. One case where
            // this c-tor will be generated is restriction of anyType.
            //
            if (has_complex_non_op_args)
            {
              CtorArgType const at (CtorArgType::complex_auto_ptr);

              os << name << "::" << endl
                 << name << " (";
              {
                CtorArgsWithoutBase ctor_args (*this, at, true, true);
                ctor_args.dispatch (c);
              }
              os << ")" << endl
                 << ": " << base << " (";
              {
                CtorBase base (*this, at, "");
                Traversal::Inherits inherits_base (base);

                inherits (c, inherits_base);
              }
              os << ")";

              if (edom_document_member_p (c))
              {
                os << "," << endl
                   << "  " << edom_document_member (c) << " (" <<
                  "::xsd::cxx::xml::dom::create_document< " << char_type <<
                  " > ())";
              }

              if (mixed)
              {
                os << "," << endl
                   << "  " << ctx.get<String> ("mixed-member") << " (this)";
              }

              {
                CtorMember t (*this, at);
                Traversal::Names n (t);

                if (gen_wildcard)
                  n >> ctor_any_;

                names (c, n);
              }

              os << "{";
              if (facets)
                os << "this->_facet_table (_xsd_" << name << "_facet_table);";
              os << "}";
            }

            // If we are generating polymorphic code then we also need to
            // provide auto_ptr version for every polymorphic type.
            //
            if (polymorphic &&
                has_poly_non_op_args && !complex_poly_args_clash)
            {
              CtorArgType const at (CtorArgType::poly_auto_ptr);

              os << name << "::" << endl
                 << name << " (";
              {
                CtorArgsWithoutBase ctor_args (*this, at, true, true);
                ctor_args.dispatch (c);
              }
              os << ")" << endl
                 << ": " << base << " (";
              {
                CtorBase base (*this, at, "");
                Traversal::Inherits inherits_base (base);

                inherits (c, inherits_base);
              }
              os << ")";

              if (edom_document_member_p (c))
              {
                os << "," << endl
                   << "  " << edom_document_member (c) << " (" <<
                  "::xsd::cxx::xml::dom::create_document< " << char_type <<
                  " > ())";
              }

              if (mixed)
              {
                os << "," << endl
                   << "  " << ctx.get<String> ("mixed-member") << " (this)";
              }

              {
                CtorMember t (*this, at);
                Traversal::Names n (t);

                if (gen_wildcard)
                  n >> ctor_any_;

                names (c, n);
              }

              os << "{";
              if (facets)
                os << "this->_facet_table (_xsd_" << name << "_facet_table);";
              os << "}";
            }
          }

          if (string_based)
          {
            // We might not have the value type if this enum is customized.
            //
            if (enum_base != 0 && enum_base->context ().count ("value"))
            {
              // c-tor (enum-value, all-non-optional-members)
              //
              CtorArgType const at (CtorArgType::type);
              String base_arg (L"_xsd_" + ename (*enum_base) + L"_base");

              os << name << "::" << endl
                 << name << " (" << fq_name (*enum_base) << "::" <<
                evalue (*enum_base) << " " << base_arg;

              {
                CtorArgsWithoutBase ctor_args (*this, at, true, false);
                ctor_args.dispatch (c);
              }

              os << ")" << endl
                 << ": " << base << " (";

              {
                CtorBase base (*this, at, base_arg);
                Traversal::Inherits inherits_base (base);

                inherits (c, inherits_base);
              }

              os << ")";

              if (edom_document_member_p (c))
              {
                os << "," << endl
                   << "  " << edom_document_member (c) << " (" <<
                  "::xsd::cxx::xml::dom::create_document< " << char_type <<
                  " > ())";
              }

              // Cannot be mixed.

              names (c, ctor_names_);

              os << "{";
              if (facets)
                os << "this->_facet_table (_xsd_" << name << "_facet_table);";
              os << "}";
            }

            CtorArgType const at (CtorArgType::type);
            String base_arg (L"_xsd_" + ename (ultimate_base (c)) + L"_base");

            // c-tor (const char*, all-non-optional-members)
            //
            os << name << "::" << endl
               << name << " (const " << char_type << "* " << base_arg;

            {
              CtorArgsWithoutBase ctor_args (*this, at, true, false);
              ctor_args.dispatch (c);
            }

            os << ")" << endl
               << ": " << base << " (";

            {
              CtorBase base (*this, at, base_arg);
              Traversal::Inherits inherits_base (base);

              inherits (c, inherits_base);
            }

            os << ")";

            if (edom_document_member_p (c))
            {
              os << "," << endl
                 << "  " << edom_document_member (c) << " (" <<
                "::xsd::cxx::xml::dom::create_document< " << char_type <<
                " > ())";
            }

            // Cannot be mixed.

            names (c, ctor_names_);

            os << "{";
            if (facets)
              os << "this->_facet_table (_xsd_" << name << "_facet_table);";
            os << "}";


            // c-tor (const std::string&, all-non-optional-members)
            //
            os << name << "::" << endl
               << name << " (const " << string_type << "& " << base_arg;

            {
              CtorArgsWithoutBase ctor_args (*this, at, true, false);
              ctor_args.dispatch (c);
            }

            os << ")" << endl
               << ": " << base << " (";

            {
              CtorBase base (*this, at, base_arg);
              Traversal::Inherits inherits_base (base);

              inherits (c, inherits_base);
            }

            os << ")";

            if (edom_document_member_p (c))
            {
              os << "," << endl
                 << "  " << edom_document_member (c) << " (" <<
                "::xsd::cxx::xml::dom::create_document< " << char_type <<
                " > ())";
            }

            // Cannot be mixed.

            names (c, ctor_names_);

            os << "{";
            if (facets)
              os << "this->_facet_table (_xsd_" << name << "_facet_table);";
            os << "}";
          }

          // c-tor (ultimate-base, all-non-optional-members)
          //
          {
            CtorArgType const at (CtorArgType::type);

            os << name << "::" << endl
               << name << " (";

            String base_arg;

            {
              CtorArgs ctor_args (*this, at, base_arg);
              ctor_args.dispatch (c);
            }

            os << ")" << endl
               << ": " << base << " (";

            {
              CtorBase base (*this, at, base_arg);
              Traversal::Inherits inherits_base (base);

              inherits (c, inherits_base);
            }

            os << ")";

            if (edom_document_member_p (c))
            {
              os << "," << endl
                 << "  " << edom_document_member (c) << " (" <<
                "::xsd::cxx::xml::dom::create_document< " << char_type <<
                " > ())";
            }

            if (mixed)
            {
              os << "," << endl
                 << "  " << ctx.get<String> ("mixed-member") << " (this)";
            }

            names (c, ctor_names_);

            os << "{";
            if (facets)
              os << "this->_facet_table (_xsd_" << name << "_facet_table);";
            os << "}";
          }

          // If we have any complex arguments in the previous c-tor
          // then also generate the auto_ptr version.
          //
          if (has_complex_non_op_args)
          {
            CtorArgType const at (CtorArgType::complex_auto_ptr);
            String base_arg;

            os << name << "::" << endl
               << name << " (";

            {
              CtorArgs ctor_args (*this, at, base_arg);
              ctor_args.dispatch (c);
            }

            os << ")" << endl
               << ": " << base << " (";

            {
              CtorBase base (*this, at, base_arg);
              Traversal::Inherits inherits_base (base);

              inherits (c, inherits_base);
            }

            os << ")";

            if (edom_document_member_p (c))
            {
              os << "," << endl
                 << "  " << edom_document_member (c) << " (" <<
                "::xsd::cxx::xml::dom::create_document< " << char_type <<
                " > ())";
            }

            if (mixed)
            {
              os << "," << endl
                 << "  " << ctx.get<String> ("mixed-member") << " (this)";
            }

            {
              CtorMember t (*this, at);
              Traversal::Names n (t);

              if (gen_wildcard)
                n >> ctor_any_;

              names (c, n);
            }

            os << "{";
            if (facets)
              os << "this->_facet_table (_xsd_" << name << "_facet_table);";
            os << "}";
          }

          // If we are generating polymorphic code then we also need to
          // provide auto_ptr version for every polymorphic type.
          //
          if (polymorphic &&
              has_poly_non_op_args && !complex_poly_args_clash)
          {
            CtorArgType const at (CtorArgType::poly_auto_ptr);
            String base_arg;

            os << name << "::" << endl
               << name << " (";

            {
              CtorArgs ctor_args (*this, at, base_arg);
              ctor_args.dispatch (c);
            }

            os << ")" << endl
               << ": " << base << " (";

            {
              CtorBase base (*this, at, base_arg);
              Traversal::Inherits inherits_base (base);

              inherits (c, inherits_base);
            }

            os << ")";

            if (edom_document_member_p (c))
            {
              os << "," << endl
                 << "  " << edom_document_member (c) << " (" <<
                "::xsd::cxx::xml::dom::create_document< " << char_type <<
                " > ())";
            }

            if (mixed)
            {
              os << "," << endl
                 << "  " << ctx.get<String> ("mixed-member") << " (this)";
            }

            {
              CtorMember t (*this, at);
              Traversal::Names n (t);

              if (gen_wildcard)
                n >> ctor_any_;

              names (c, n);
            }

            os << "{";
            if (facets)
              os << "this->_facet_table (_xsd_" << name << "_facet_table);";
            os << "}";
          }


          // copy c-tor
          //

          os << name << "::" << endl
             << name << " (const " << name << "& x," << endl
             << flags_type << " f," << endl
             << container << "* c)" << endl
             << ": " << base << " (x, f, c)";

          if (edom_document_member_p (c))
          {
            os << "," << endl
               << "  " << edom_document_member (c) << " (" <<
              "::xsd::cxx::xml::dom::create_document< " << char_type <<
              " > ())";
          }

          if (mixed)
          {
            String const& m (ctx.get<String> ("mixed-member"));
            os << "," << endl
               << "  " << m << " (x." << m << ", f, this)";
          }

          if (ordered)
          {
            String const& m (ctx.get<String> ("order-member"));
            os << "," << endl
               << "  " << m << " (x." << m << ")";
          }

          {
            CopyAny copy_any (*this, "x");
            CopyMember copy_member (*this, "x");
            Traversal::Names names;

            names >> copy_member;

            if (gen_wildcard)
              names >> copy_any;

            Complex::names (c, names);
          }

          os << "{";
          if (facets)
            os << "this->_facet_table (_xsd_" << name << "_facet_table);";
          os << "}";

          //
          //
          bool he (has<Traversal::Element> (c));
          bool hae (has<Traversal::Any> (c));

          bool ha (has<Traversal::Attribute> (c));
          bool haa (has<Traversal::AnyAttribute> (c));

          //
          //
          if (!options.suppress_parsing ())
          {
            // c-tor (xercesc::DOMElement)
            //
            os << name << "::" << endl
               << name << " (const " << xerces_ns << "::DOMElement& e," << endl
               << flags_type << " f," << endl
               << container << "* c)" << endl
               << ": " << base << " (e, f";

            if (he || ha || hae || (haa && gen_wildcard) || mixed)
              os << " | " << flags_type << "::base";

            os << ", c)";

            if (edom_document_member_p (c))
            {
              os << "," << endl
                 << "  " << edom_document_member (c) << " (" <<
                "::xsd::cxx::xml::dom::create_document< " << char_type <<
                " > ())";
            }

            if (mixed)
            {
              os << "," << endl
                 << "  " << ctx.get<String> ("mixed-member") << " (this)";
            }

            names (c, element_ctor_names_);

            os << "{";

            if (facets)
              os << "this->_facet_table (_xsd_" << name << "_facet_table);"
                 << endl;

            bool base_has_el (false), base_has_at (false);

            // We are only interested in this information if we are
            // generating our own parse().
            //
            if (he || ha || hae || (haa && gen_wildcard) || mixed)
            {
              if (c.inherits_p ())
              {
                HasParseFunction test (*this, base_has_el, base_has_at);
                test.dispatch (c.inherits ().base ());
              }
            }

            //@@ Throw if p is not exhausted at the end.
            //
            if (he || ha || hae || (haa && gen_wildcard) || mixed)
              os << "if ((f & " << flags_type << "::base) == 0)"
                 << "{"
                 << parser_type << " p (e, " <<
                (he || hae || base_has_el || mixed_p (c) ? "true, " : "false, ") <<
                (mixed_p (c) ? "true, " : "false, ") <<
                (ha || (haa && gen_wildcard) || base_has_at ? "true" : "false")
                 << ");"
                 << "this->" << unclash (name, "parse") << " (p, f);"
                 << "}";

            os << "}";

            bool simple (true);
            {
              IsSimpleType t (simple);
              t.dispatch (c);
            }

            if (simple)
            {
              // c-tor (xercesc::DOMAttr)
              //
              os << name << "::" << endl
                 << name << " (const " << xerces_ns << "::DOMAttr& a," << endl
                 << flags_type << " f," << endl
                 << container << "* c)" << endl
                 << ": " << base << " (a, f, c)"
                 << "{";

              if (facets)
                os << "this->_facet_table (_xsd_" << name << "_facet_table);";

              os << "}";

              // c-tor (string const&, xercesc::DOMElement)
              //
              os << name << "::" << endl
                 << name << " (const " << string_type << "& s," << endl
                 << "const " << xerces_ns << "::DOMElement* e," << endl
                 << flags_type << " f," << endl
                 << container << "* c)" << endl
                 << ": " << base << " (s, e, f, c)"
                 << "{";

              if (facets)
                os << "this->_facet_table (_xsd_" << name << "_facet_table);";

              os << "}";
            }

            if (he || ha || hae || (haa && gen_wildcard) || mixed)
            {
              os << "void " << name << "::" << endl
                 << unclash (name, "parse") << " (" <<
                parser_type << "& p," << endl
                 << flags_type <<
                (he || ha || base_has_el || base_has_at ? " f" : "") << ")"
                 << "{";

              // Allow the base to parse its part.
              //
              if (base_has_el || base_has_at)
                os << "this->" << base << "::parse (p, f);"
                   << endl;

              if (he || hae || mixed_p (c))
              {
                bool m (mixed_p (c));

                os << "for (; p.more_content (); p.next_content (" <<
                  (m ? "true" : "false") << "))"
                   << "{";

                if (m)
                {
                  String const& ma (ctx.get<String> ("mixed-aname"));
                  String const& mi (ctx.get<String> ("mixed-ordered-id-name"));
                  String const& oa (ctx.get<String> ("order-aname"));
                  String const& ot (ctx.get<String> ("order-type"));

                  os << "if (p.cur_is_text ())"
                     << "{"
                     << "const " << xerces_ns << "::DOMText& t (" <<
                    "p.cur_text ());"
                     << "this->" << ma << " ().push_back (" << endl
                     << "::xsd::cxx::xml::transcode< " << char_type << " > (" <<
                    "t.getData (), t.getLength ()));"
                     << "this->" << oa << " ().push_back (" << endl
                     << ot << " (" << mi << "," << endl
                     << "this->" << ma << " ().size () - 1));"
                     << "continue;"
                     << "}";
                }

                if (he || hae)
                {
                  os << "const " << xerces_ns << "::DOMElement& i (" <<
                    "p.cur_element ());"
                     << "const " << qname_type << " n (" << endl
                     << "::xsd::cxx::xml::dom::name< " << char_type << " > (i));"
                     << endl;

                  names (c, names_element_);
                }

                os << "break;"
                   << "}";

                // Make sure all non-optional elements are set.
                //
                names (c, names_element_test_);
              }

              if (ha || (haa && gen_wildcard))
              {
                if (base_has_at)
                  os << "p.reset_attributes ();"
                     << endl;

                os << "while (p.more_attributes ())"
                   << "{"
                   << "const " << xerces_ns << "::DOMAttr& i (" <<
                  "p.next_attribute ());"
                   << "const " << qname_type << " n (" << endl
                   << "::xsd::cxx::xml::dom::name< " << char_type << " > (i));"
                   << endl;

                names (c, names_attribute_);

                // Generate anyAttribute code after all the attributes.
                //
                if (gen_wildcard)
                  names (c, names_any_attribute_);


                // os << "{"  // else block
                // @@
                // This doesn't play well with inheritance because we
                // don't expect base's attributes. Also there are other
                // "special" attributes such as xmlns, etc.
                //
                // << "throw ::xsd::cxx::tree::unexpected_attribute ... "
                // << "}";

                os << "}"; // while loop

                // Make sure all non-optional attributes are set.
                //
                names (c, names_attribute_test_);
              }

              os << "}";
            }
          }

          // _clone
          //
          if (!(c.abstract_p () ||
                (renamed && polymorphic && polymorphic_p (c))))
            os << name << "* " << name << "::" << endl
               << "_clone (" << flags_type << " f," << endl
               << container << "* c) const"
               << "{"
               << "return new class " << name << " (*this, f, c);"
               << "}";

          // operator=
          //
          if (!options.suppress_assignment () &&
              (he || ha || (gen_wildcard && (hae || haa))))
          {
            os << name << "& " << name << "::" << endl
               << "operator= (const " << name << "& x)"
               << "{"
               << "if (this != &x)"
               << "{"
               << "static_cast< " << base << "& > (*this) = x;";

            // Note that here we don't assign the DOMDocument that is
            // used to hold wildcard fragments. Each document has its
            // own copy.

            // Mixed text content.
            //
            if (mixed)
            {
              String const& m (ctx.get<String> ("mixed-member"));
              os << "this->" << m << " = x." << m << ";";
            }

            // Order container.
            //
            if (ordered)
            {
              String const& m (ctx.get<String> ("order-member"));
              os << "this->" << m << " = x." << m << ";";
            }

            names (c, assign_names_);

            os << "}"
               << "return *this;"
               << "}";
          }

          // d-tor
          //
          os << name << "::" << endl
             << "~" << name << " ()"
             << "{"
             << "}";

          // Register with type factory map.
          //
          if (polymorphic && polymorphic_p (c) && !c.abstract_p ())
          {
            // Note that we are using the original type name.
            //
            String const& name (ename (c));

            // If this type is anonymous but substitutes, then it will
            // be registered as part of the substitution registration.
            //
            if (!anonymous_p (c) && !options.suppress_parsing ())
            {
              os << "static" << endl
                 << "const ::xsd::cxx::tree::type_factory_initializer< " <<
                poly_plate << ", " << char_type << ", " << name << " >" << endl
                 << "_xsd_" << name << "_type_factory_init (" << endl
                 << strlit (c.name ()) << "," << endl
                 << strlit (xml_ns_name (c)) << ");"
                 << endl;
            }

            if ((!anonymous_p (c) || anonymous_substitutes_p (c)) &&
                options.generate_comparison ())
            {
              os << "static" << endl
                 << "const ::xsd::cxx::tree::comparison_initializer< " <<
                poly_plate << ", " << char_type << ", " << name << " >" << endl
                 << "_xsd_" << name << "_comparison_init;"
                 << endl;
            }
          }

          // Comparison operators.
          //
          if (options.generate_comparison () &&
              (he || ha || mixed || ordered || !c.inherits_p () ||
               ((hae || haa) && gen_wildcard)))
          {
            bool base_comp (false);

            if (c.inherits_p ())
            {
              HasComparisonOperator test (*this, base_comp);
              test.dispatch (c.inherits ().base ());
            }

            bool has_body (he || ha || ordered || mixed || base_comp ||
                           ((hae || haa) && gen_wildcard));

            os << "bool" << endl
               << "operator== (const " << name << "&" <<
              (has_body ? " x" : "") << ", " <<
              "const " << name << "&" << (has_body ? " y" : "") << ")"
               << "{";

            if (base_comp)
              os << "if (!(static_cast< const " << base << "& > (x) ==" << endl
                 << "static_cast< const " << base << "& > (y)))" << endl
                 << "return false;"
                 << endl;

            {
              Complex::names (c, comparison_names_);
            }

            if (mixed)
            {
              String const& an (ctx.get<String> ("mixed-aname"));
              os << "if (!(x." << an << " () == y." << an << " ()))" << endl
                 << "return false;"
                 << endl;
            }

            if (ordered)
            {
              String const& an (ctx.get<String> ("order-aname"));
              os << "if (!(x." << an << " () == y." << an << " ()))" << endl
                 << "return false;"
                 << endl;
            }

            os << "return true;"
               << "}";

            os << "bool" << endl
               << "operator!= (const " << name << "& x, " <<
              "const " << name << "& y)"
               << "{"
               << "return !(x == y);"
               << "}";
          }
        }

      private:
        Traversal::Inherits inherits_member_;
        MemberTypeName member_name_;

        Traversal::Names names_element_;
        Traversal::Names names_element_test_;

        Traversal::Names names_attribute_;
        Traversal::Names names_any_attribute_;
        Traversal::Names names_attribute_test_;

        Any any_;
        Element element_;

        AnyTest any_test_;
        ElementTest element_test_;

        Attribute attribute_;
        AttributeTest attribute_test_;

        AnyAttribute any_attribute_;

        DefaultCtorAnyInit default_ctor_any_init_;
        DefaultCtorMemberInit default_ctor_member_init_;
        Traversal::Names default_ctor_init_names_;

        CtorAny ctor_any_;
        CtorMember ctor_member_;
        Traversal::Names ctor_names_;

        ElementCtorAny element_ctor_any_;
        ElementCtorMember element_ctor_member_;
        Traversal::Names element_ctor_names_;

        AssignAny assign_any_;
        AssignMember assign_member_;
        Traversal::Names assign_names_;

        AnyComparison comparison_any_;
        MemberComparison comparison_member_;
        Traversal::Names comparison_names_;

        FacetArray facet_array_;
      };


      // Generate element types and substitution group map entries.
      //
      struct GlobalElement: Traversal::Element,
                            GlobalElementBase,
                            Context
      {
        GlobalElement (Context& c)
            : GlobalElementBase (c),
              Context (c),
              element_type_ (c.options.generate_element_type ()),
              element_map_ (c.options.generate_element_map ()),
              type_name_ (c)
        {
          belongs_ >> type_name_;
        }

        virtual void
        traverse (Type& e)
        {
          SemanticGraph::Type& t (e.type ());

          // Check if this element is abstract.
          //
          bool abst;
          {
            SemanticGraph::Complex* tc;
            abst = (tc = dynamic_cast<SemanticGraph::Complex*> (&t)) != 0 &&
              tc->abstract_p ();
          }

          if (!abst && element_type_ && doc_root_p (e))
          {
            bool fund (false);
            {
              IsFundamentalType test (fund);
              test.dispatch (t);
            }

            bool simple (true);
            if (!fund)
            {
              IsSimpleType test (simple);
              test.dispatch (t);
            }

            String const& name (ename (e));
            String const& type (etype (e));
            String const& member (emember (e));

            os << "// " << name << endl
               << "// " << endl
               << endl;

            // Virtual accessors.
            //
            os << "const " << any_type << "* " << name << "::" << endl
               << "_value () const"
               << "{";

            if (fund)
              os << "return 0;";
            else
              os << "return &this->" << member << ".get ();";

            os << "}";

            os << any_type << "* " << name << "::" << endl
               << "_value ()"
               << "{";

            if (fund)
              os << "return 0;";
            else
              os << "return &this->" << member << ".get ();";

            os << "}";

            // default c-tor
            //
            if (options.generate_default_ctor ())
            {
              os << name << "::" << endl
                 << name << " ()" << endl
                 << ": " << member << " (0)"
                 << "{"
                 << "}";
            }

            // c-tor (value)
            //
            os << name << "::" << endl
               << name << " (const " << type << "& x)" << endl
               << ": " << member << " (x, 0)"
               << "{"
               << "}";


            // c-tor (auto_ptr<value>)
            //
            if (!simple || (polymorphic && polymorphic_p (t)))
            {
              os << name << "::" << endl
                 << name << " (" << auto_ptr << "< " << type << " > p)" << endl
                 << ": " << member << " (" <<
                (std >= cxx_version::cxx11 ? "::std::move (p)" : "p") << ", 0)"
                 << "{"
                 << "}";
            }

            // c-tor (xercesc::DOMElement)
            //
            SemanticGraph::Context& ec (e.context ());
            String const& name_member (ec.get<String> ("element-name-member"));
            String const& ns_member (ec.get<String> ("element-ns-member"));

            bool parsing (!options.suppress_parsing ());
            if (parsing)
            {
              String const& tr (etraits (e));

              os << name << "::" << endl
                 << name << " (const " << xerces_ns << "::DOMElement& e, " <<
                flags_type << " f)" << endl
                 << ": " << member << " (0)"
                 << "{"
                 << "const " << qname_type << " n (" << endl
                 << "::xsd::cxx::xml::dom::name< " << char_type << " > (e));"
                 << endl
                 << "if (n.name () == " << name_member << " && " <<
                "n.namespace_ () == " << ns_member << ")" << endl
                 << "this->" << member << ".set (" << tr <<
                "::create (e, f, 0));"
                 << "else" << endl
                 << "throw ::xsd::cxx::tree::unexpected_element < " <<
                char_type << " > (" << endl
                 << "n.name (), n.namespace_ ()," << endl
                 << name_member << ", " << ns_member << ");"
                 << "}";
            }

            // copy c-tor
            //
            os << name << "::" << endl
               << name << " (const " << name << "& x, " <<
              flags_type << " f)" << endl
               << ": " << element_type << " ()," << endl
               << "  " << member << " (x." << member << ", f, 0)"
               << "{"
               << "}";

            // _clone
            //
            os << name << "* " << name << "::" << endl
               << "_clone (" << flags_type << " f) const"
               << "{"
               << "return new class " << name << " (*this, f);"
               << "}";

            // Element name and namespace accessors.
            //
            String const& aname (ec.get<String> ("element-name"));
            String const& ans (ec.get<String> ("element-ns"));

            os << "const " << string_type << "& " << name << "::" << endl
               << aname << " ()"
               << "{"
               << "return " << name_member << ";"
               << "}";

            os << "const " << string_type << "& " << name << "::" << endl
               << ans << " ()"
               << "{"
               << "return " << ns_member << ";"
               << "}";

            os << "const " << string_type << "& " << name << "::" << endl
               << "_name () const"
               << "{"
               << "return " << name_member << ";"
               << "}";

            os << "const " << string_type << "& " << name << "::" << endl
               << "_namespace () const"
               << "{"
               << "return " << ns_member << ";"
               << "}";

            os << "const " << string_type << " " << name << "::" << endl
               << name_member << " (" << strlit (e.name ()) << ");"
               << endl
               << "const " << string_type << " " << name << "::" << endl
               << ns_member << " (" << strlit (e.namespace_ ().name ()) << ");"
               << endl;

            // d-tor
            //
            os << name << "::" << endl
               << "~" << name << " ()"
               << "{"
               << "}";

            // Element map registration.
            //
            if (element_map_ && parsing)
            {
              os << "static " << endl
                 << "const ::xsd::cxx::tree::parser_init< " << name << ", " <<
                char_type << ", " << any_type << " >" << endl
                 << "_xsd_" << name << "_parser_init (" <<
                name << "::" << aname << " (), " <<
                name << "::" << ans << " ());"
                 << endl;
            }
          }

          if (!abst && polymorphic && e.substitutes_p () &&
              !options.suppress_parsing ())
          {
            String const& name (ename (e));
            Type& r (e.substitutes ().root ());

            os << "static" << endl
               << "const ::xsd::cxx::tree::element_factory_initializer< " <<
              poly_plate << ", " << char_type << ", ";

            belongs (e, belongs_);

            os << " >" << endl
               << "_xsd_" << name << "_element_factory_init (" << endl
               << strlit (r.name ()) << "," << endl
               << strlit (r.namespace_ ().name ()) << "," << endl
               << strlit (e.name ()) << "," << endl
               << strlit (e.namespace_ ().name ()) << ");"
               << endl
               << endl;
          }
        }

      private:
        bool element_type_;
        bool element_map_;
        Traversal::Belongs belongs_;
        MemberTypeName type_name_;
      };
    }

    void
    generate_tree_source (Context& ctx, size_t first, size_t last)
    {
      if (ctx.options.generate_wildcard ())
      {
        ctx.os << "#include <libxsd/cxx/xml/dom/wildcard-source.hxx>" << endl
               << endl;
      }

      if (!ctx.options.suppress_parsing ())
        ctx.os << "#include <libxsd/cxx/xml/dom/parsing-source.hxx>" << endl
               << endl;

      if (ctx.polymorphic)
      {
        bool parsing (!ctx.options.suppress_parsing ());
        bool comparison (ctx.options.generate_comparison ());

        if (parsing)
          ctx.os << "#include <libxsd/cxx/tree/type-factory-map.hxx>" << endl
                 << endl;

        if (comparison)
          ctx.os << "#include <libxsd/cxx/tree/comparison-map.hxx>" << endl
                 << endl;

        if (parsing || comparison)
        {
          bool import_maps (ctx.options.import_maps ());
          bool export_maps (ctx.options.export_maps ());

          if (import_maps || export_maps)
          {
            ctx.os << "#ifndef XSD_NO_EXPORT" << endl
                   << endl
                   << "namespace xsd"
                   << "{"
                   << "namespace cxx"
                   << "{"
                   << "namespace tree"
                   << "{"
                   << "#ifdef _MSC_VER" << endl;

            if (parsing && export_maps)
              ctx.os << "template struct __declspec (dllexport) " <<
                "type_factory_plate< " << ctx.poly_plate << ", " <<
                ctx.char_type << " >;";

            if (parsing && import_maps)
              ctx.os << "template struct __declspec (dllimport) " <<
                "type_factory_plate< " << ctx.poly_plate << ", " <<
                ctx.char_type << " >;";

            if (comparison && export_maps)
              ctx.os << "template struct __declspec (dllexport) " <<
                "comparison_plate< " << ctx.poly_plate << ", " <<
                ctx.char_type << " >;";

            if (comparison && import_maps)
              ctx.os << "template struct __declspec (dllimport) " <<
                "comparison_plate< " << ctx.poly_plate << ", " <<
                ctx.char_type << " >;";

            ctx.os << "#elif defined(__GNUC__) && __GNUC__ >= 4" << endl;

            if (parsing)
              ctx.os << "template struct __attribute__ ((visibility(\"default\"))) " <<
                "type_factory_plate< " << ctx.poly_plate << ", " <<
                ctx.char_type << " >;";

            if (comparison)
              ctx.os << "template struct __attribute__ ((visibility(\"default\"))) " <<
                "comparison_plate< " << ctx.poly_plate << ", " <<
                ctx.char_type << " >;";

            ctx.os << "#elif defined(XSD_MAP_VISIBILITY)" << endl;

            if (parsing)
              ctx.os << "template struct XSD_MAP_VISIBILITY " <<
                "type_factory_plate< " << ctx.poly_plate << ", " <<
                ctx.char_type << " >;";

            if (comparison)
              ctx.os << "template struct XSD_MAP_VISIBILITY " <<
                "comparison_plate< " << ctx.poly_plate << ", " <<
                ctx.char_type << " >;";

            ctx.os << "#endif" << endl
                   << "}"  // tree
                   << "}"  // cxx
                   << "}"  // xsd
                   << "#endif // XSD_NO_EXPORT" << endl
                   << endl;
          }

          ctx.os << "namespace _xsd"
                 << "{";

          if (parsing)
            ctx.os << "static" << endl
                   << "const ::xsd::cxx::tree::type_factory_plate< " <<
              ctx.poly_plate << ", " << ctx.char_type << " >" << endl
                   << "type_factory_plate_init;"
                   << endl;

          if (comparison)
            ctx.os << "static" << endl
                   << "const ::xsd::cxx::tree::comparison_plate< " <<
              ctx.poly_plate << ", " << ctx.char_type << " >" << endl
                   << "comparison_plate_init;"
                   << endl;

          ctx.os << "}";
        }
      }

      Traversal::Schema schema;
      Sources sources;
      Traversal::Names names_ns, names;
      Namespace ns (ctx, first, last);

      List list (ctx);
      Union union_ (ctx);
      Complex complex (ctx);
      Enumeration enumeration (ctx);
      GlobalElement element (ctx);

      schema >> sources >> schema;
      schema >> names_ns >> ns >> names;

      names >> list;
      names >> union_;
      names >> complex;
      names >> enumeration;
      names >> element;

      schema.dispatch (ctx.schema_root);
    }
  }
}

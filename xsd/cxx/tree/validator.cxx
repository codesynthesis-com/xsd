// file      : xsd/cxx/tree/validator.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <set>
#include <iostream>

#include <cxx/tree/validator.hxx>

#include <xsd-frontend/semantic-graph.hxx>
#include <xsd-frontend/traversal.hxx>

#include <cxx/tree/elements.hxx>

using namespace std;

namespace CXX
{
  namespace Tree
  {
    namespace
    {
      class ValidationContext: public Context
      {
      public:
        ValidationContext (SemanticGraph::Schema& root,
                           SemanticGraph::Path const& path,
                           Tree::options const& ops,
                           const WarningSet& disabled_warnings,
                           Counts const& counts,
                           bool generate_xml_schema,
                           bool& valid_)
            : Context (std::wcerr,
                       root,
                       path,
                       ops,
                       counts,
                       generate_xml_schema,
                       0,
                       0,
                       0,
                       0),
              disabled_warnings_ (disabled_warnings),
              disabled_warnings_all_ (false),
              valid (valid_),
              subst_group_warning_issued (subst_group_warning_issued_),
              subst_group_warning_issued_ (false)
        {
          if (disabled_warnings_.find ("all") != disabled_warnings_.end ())
            disabled_warnings_all_ = true;
        }

      public:
        bool
        is_disabled (char const* w)
        {
          return disabled_warnings_all_ ||
            disabled_warnings_.find (w) != disabled_warnings_.end ();
        }

      public:
        String
        xpath (SemanticGraph::Nameable& n)
        {
          if (n.is_a<SemanticGraph::Namespace> ())
            return L"<namespace-level>"; // There is a bug if you see this.

          if (n.named_p ())
          {
            SemanticGraph::Scope& scope (n.scope ());

            if (scope.is_a<SemanticGraph::Namespace> ())
              return n.name ();

            return xpath (scope) + L"/" + n.name ();
          }
          else
          {
            return L"(anonymous type for " +
              n.context ().get<String> ("instance-name") + L")";
          }
        }

      protected:
        ValidationContext (ValidationContext& c)
            :  Context (c),
               disabled_warnings_ (c.disabled_warnings_),
               disabled_warnings_all_ (c.disabled_warnings_all_),
               valid (c.valid),
               subst_group_warning_issued (c.subst_group_warning_issued)
        {
        }

      protected:
        const WarningSet& disabled_warnings_;
        bool disabled_warnings_all_;

        bool& valid;

        bool& subst_group_warning_issued;
        bool subst_group_warning_issued_;
      };


      //
      //
      struct Any: Traversal::Any, ValidationContext
      {
        Any (ValidationContext& c)
            : ValidationContext (c)
        {
        }

        struct Element: Traversal::Element, ValidationContext
        {
          Element (ValidationContext& c, SemanticGraph::Any& any)
              : ValidationContext (c),
                any_ (any),
                ns_ (any.definition_namespace ().name ())
          {
          }

          virtual void
          traverse (SemanticGraph::Element& e)
          {
	    if (skip (e))
              return;

            using SemanticGraph::Any;

            bool q (e.qualified_p ());
            String ns (q ? e.namespace_ ().name () : "");

            for (Any::NamespaceIterator i (any_.namespace_begin ());
                 i != any_.namespace_end (); ++i)
            {
              bool failed (false);

              if (*i == L"##any")
              {
                failed = true;
              }
              else if (*i == L"##other")
              {
                if (ns_)
                {
                  // Note that here I assume that ##other does not
                  // include names without target namespace. This
                  // is not what the spec says but that seems to be
                  // the consensus.
                  //
                  failed = q && ns != ns_;
                }
                else
                {
                  // No target namespace.
                  //
                  failed = q && ns != L"";
                }
              }
              else if (*i == L"##local")
              {
                failed = !q || ns == L"";
              }
              else if (*i == L"##targetNamespace")
              {
                failed = (q && ns_ == ns) || (!q && ns_ == L"");
              }
              else
              {
                failed = q && *i == ns;
              }

              if (failed)
              {
                Any& a (any_);

                os << a.file () << ":" << a.line () << ":" << a.column ()
                   << ": warning T001: namespace '" << *i << "' allows for "
                   << "element '" << e.name () << "'" << endl;

                os << a.file () << ":" << a.line () << ":" << a.column ()
                   << ": warning T001: generated code may not associate element '"
                   << e.name () << "' correctly if it appears in place of "
                   << "this wildcard" << endl;

                os << e.file () << ":" << e.line () << ":" << e.column ()
                   << ": info: element '" << e.name () << "' is defined "
                   << "here" << endl;
              }
            }
          }

        private:
          SemanticGraph::Any& any_;
          String ns_;
        };

        struct Complex: Traversal::Complex
        {
          Complex ()
              : up_ (true), down_ (true)
          {
          }

          virtual void
          post (Type& c)
          {
            // Go down the inheritance hierarchy.
            //
            if (down_)
            {
              bool up = up_;
              up_ = false;

              if (c.inherits_p ())
                dispatch (c.inherits ().base ());

              up_ = up;
            }

            // Go up the inheritance hierarchy.
            //
            if (up_)
            {
              bool down = down_;
              down_ = false;

              for (Type::BegetsIterator i (c.begets_begin ());
                   i != c.begets_end (); ++i)
              {
                dispatch (i->derived ());
              }

              down_ = down;
            }
          }

        private:
          bool up_, down_;
        };

        virtual void
        traverse (SemanticGraph::Any& a)
        {
          using SemanticGraph::Compositor;

          // Find our complex type.
          //
          Compositor* c (&a.contained_particle ().compositor ());

          while(!c->contained_compositor_p ())
            c = &c->contained_particle ().compositor ();

          SemanticGraph::Complex& type (
            dynamic_cast<SemanticGraph::Complex&> (
              c->contained_compositor ().container ()));

          Complex complex;
          Traversal::Names names;
          Element element (*this, a);

          complex >> names >> element;

          complex.dispatch (type);
        }
      };


      //
      //
      struct Traverser: Traversal::Schema,
                        Traversal::Complex,
                        Traversal::Type,
                        Traversal::Element,
                        ValidationContext
      {
        Traverser (ValidationContext& c)
            : ValidationContext (c), any_ (c)
        {
          *this >> sources_ >> *this;
          *this >> schema_names_ >> ns_ >> names_;

          names_ >> *this >> names_;

          // Any
          //
          if (!is_disabled ("T001"))
          {
            *this >> contains_compositor_ >> compositor_ >> contains_particle_;
            contains_particle_ >> compositor_;
            contains_particle_ >> any_;
          }
        }

        virtual void
        traverse (SemanticGraph::Complex& c)
        {
          using SemanticGraph::Schema;

          traverse (static_cast<SemanticGraph::Type&> (c));

          if (c.inherits_p ())
          {
            SemanticGraph::Type& t (c.inherits ().base ());

            if (t.named_p () &&
                types_.find (
                  t.scope ().name () + L"#" + t.name ()) == types_.end ())
            {
              // Don't worry about types that are in included/imported
              // schemas.
              //
              Schema& s (dynamic_cast<Schema&> (t.scope ().scope ()));

              if (&s == &schema_root || sources_p (schema_root, s))
              {
                valid = false;

                os << c.file () << ":" << c.line () << ":" << c.column ()
                   << ": error: type '" << xpath (c) << "' inherits from "
                   << "yet undefined type '" << xpath (t) << "'" << endl;

                os << t.file () << ":" << t.line () << ":" << t.column ()
                   << ": info: '" << xpath (t) << "' is defined here"
                   << endl;

                os << c.file () << ":" << c.line () << ":" << c.column ()
                   << ": info: inheritance from a yet-undefined type is "
                   << "not supported" << endl;

                os << c.file () << ":" << c.line () << ":" << c.column ()
                   << ": info: re-arrange your schema and try again"
                   << endl;
              }
            }
          }

          Complex::traverse (c);
        }

        virtual void
        traverse (SemanticGraph::Type& t)
        {
          // This is also used to traverse Complex.
          //
          if (t.named_p ())
          {
            types_.insert (t.scope ().name () + L"#" + t.name ());
          }
        }

        virtual void
        traverse (SemanticGraph::Element& e)
        {
          if (is_disabled ("T002"))
            return;

          // Note that there is no test for generate_p since we want
          // to catch cases when things are not being generated but
          // most likely should have been.
          //
          if (e.substitutes_p () && !polymorphic &&
              !subst_group_warning_issued)
          {
            subst_group_warning_issued = true;

            os << e.file () << ":" << e.line () << ":" << e.column ()
               << ": warning T002: substitution groups are used but "
               << "--generate-polymorphic was not specified" << endl;

            os << e.file () << ":" << e.line () << ":" << e.column ()
               << ": info: generated code may not be able to handle "
               << "some conforming instances" << endl;
          }
        }

        // Return true if root sources s.
        //
        bool
        sources_p (SemanticGraph::Schema& root, SemanticGraph::Schema& s)
        {
          using SemanticGraph::Schema;
          using SemanticGraph::Sources;

          for (Schema::UsesIterator i (root.uses_begin ());
               i != root.uses_end (); ++i)
          {
            if (i->is_a<Sources> ())
            {
              if (&i->schema () == &s || sources_p (i->schema (), s))
                return true;
            }
          }

          return false;
        }

      private:
        set<String> types_;

        Sources sources_;

        Traversal::Names schema_names_;
        Traversal::Namespace ns_;

        Traversal::Names names_;

        // Any.
        //
        Any any_;
        Traversal::Compositor compositor_;
        Traversal::ContainsParticle contains_particle_;
        Traversal::ContainsCompositor contains_compositor_;
      };


      struct AnonymousType: Traversal::Schema,
                            Traversal::Complex,
                            Traversal::Element,
                            Traversal::Attribute,
                            ValidationContext
      {
        AnonymousType (ValidationContext& c)
            : ValidationContext (c),
              anonymous_error_issued_ (false)
        {
          *this >> sources_ >> *this;
          *this >> schema_names_ >> ns_ >> names_ >> *this;
          *this >> names_;
        }

        bool
        traverse_common (SemanticGraph::Member& m)
        {
          SemanticGraph::Type& t (m.type ());

          if (!t.named_p ()
              && !t.is_a<SemanticGraph::Fundamental::IdRef> ()
              && !t.is_a<SemanticGraph::Fundamental::IdRefs> ())
          {
            if (!anonymous_error_issued_)
            {
              valid = false;
              anonymous_error_issued_ = true;

              wcerr << t.file ()
                    << ": error: anonymous types detected"
                    << endl;

              wcerr << t.file ()
                    << ": info: "
                    << "anonymous types are not supported in this mapping"
                    << endl;

              wcerr << t.file ()
                    << ": info: consider explicitly naming these types or "
                    << "remove the --preserve-anonymous option to "
                    << "automatically name them"
                    << endl;

              if (!options.show_anonymous ())
                wcerr << t.file ()
                      << ": info: use --show-anonymous option to see these "
                      << "types" << endl;
            }

            return true;
          }

          return false;
        }

        virtual void
        traverse (SemanticGraph::Element& e)
        {
	  if (skip (e)) return;

          if (traverse_common (e))
          {
            if (options.show_anonymous ())
            {
              wcerr << e.file () << ":" << e.line () << ":" << e.column ()
                    << ": error: element '" << xpath (e) << "' "
                    << "is of anonymous type" << endl;
            }
          }
          else
            Traversal::Element::traverse (e);
        }

        virtual void
        traverse (SemanticGraph::Attribute& a)
        {
          if (traverse_common (a))
          {
            if (options.show_anonymous ())
            {
              wcerr << a.file () << ":" << a.line () << ":" << a.column ()
                    << ": error: attribute '" << xpath (a) << "' "
                    << "is of anonymous type" << endl;
            }
          }
          else
            Traversal::Attribute::traverse (a);
        }

      private:
        bool anonymous_error_issued_;

        set<String> types_;

        Sources sources_;

        Traversal::Names schema_names_;
        Traversal::Namespace ns_;

        Traversal::Names names_;
      };
    }

    bool Validator::
    validate (options const& ops,
              SemanticGraph::Schema& schema,
              SemanticGraph::Path const& path,
              const WarningSet& disabled_warnings,
              Counts const& counts)
    {
      bool valid (true);
      ValidationContext ctx (
        schema, path, ops, disabled_warnings, counts, false, valid);

      //
      //
      bool import_maps (ops.import_maps ());
      bool export_maps (ops.export_maps ());

      if (import_maps && export_maps)
      {
        wcerr << "error: --import-maps and --export-maps are "
              << "mutually exclusive" << endl;

        return false;
      }

      if (import_maps && !ctx.polymorphic)
      {
        wcerr << "error: --import-maps can only be specified together with "
              << "--generate-polymorphic" << endl;

        return false;
      }

      if (export_maps && !ctx.polymorphic)
      {
        wcerr << "error: --export-maps can only be specified together " <<
          "with --generate-polymorphic" << endl;

        return false;
      }

      //
      //
      if (ops.char_type () != "char" &&
          ops.char_type () != "wchar_t" &&
          !ctx.is_disabled ("T003"))
      {
        wcerr << "warning T003: unknown base character type '" <<
          ops.char_type ().c_str () << "'" << endl;
      }

      //
      //
      NarrowString tn (ops.type_naming ());

      if (tn != "knr" && tn != "ucc" && tn != "java")
      {
        wcerr << "error: unknown type naming style specified: '" <<
          tn.c_str () << "'" << endl;

        return false;
      }

      NarrowString fn (ops.function_naming ());

      if (fn != "knr" && fn != "lcc" && fn != "java")
      {
        wcerr << "error: unknown function naming style specified: '" <<
          fn.c_str () << "'" << endl;

        return false;
      }

      //
      //
      bool element_type (ops.generate_element_type ());
      bool par (!ops.suppress_parsing ());
      bool ser (ops.generate_serialization ());

      if (ops.generate_element_map ())
      {
        if (!element_type)
        {
          wcerr << "error: --generate-element-map can only be specified " <<
            "together with --generate-element-type" << endl;

          return false;
        }

        if (!(par || ser))
        {
          wcerr << "error: --generate-element-map is specified but " <<
            "neither parsing nor serialization code is generated" << endl;

          return false;
        }
      }

      // Issue a warning if there are more than one global element
      // and we are generating parsing/serialization functions or
      // element types for all of them by default.
      //

      if (counts.global_elements > 1 &&
          (element_type || par || ser) &&
          !ops.root_element_first () &&
          !ops.root_element_last () &&
          !ops.root_element_all () &&
          !ops.root_element_none () &&
          ops.root_element ().empty () &&
          !ctx.is_disabled ("T004"))
      {
        wcerr << schema.file () << ": warning T004: generating ";

        if (element_type)
          wcerr << "element types";
        else
        {
          wcerr << (par ? "parsing " : "") <<
            (ser ? (par ? "and serialization " : "serialization ") : "") <<
            "functions";
        }
        wcerr << " for " << counts.global_elements << " global elements" <<
          endl;

        wcerr << schema.file () << ": info: use --root-element-* options "
              << "to specify document root(s)" << endl;
      }


      // Test for anonymout types.
      //
      {
        AnonymousType traverser (ctx);
        traverser.dispatch (schema);
      }

      // Test the rest.
      //
      if (valid)
      {
        Traverser traverser (ctx);
        traverser.dispatch (schema);
      }

      return valid;

      // T005 is used in polymorphism-processor.cxx.
      //
    }
  }
}

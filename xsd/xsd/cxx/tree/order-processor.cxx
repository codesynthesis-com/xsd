// file      : xsde/cxx/tree/order-processor.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <iostream>

#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/order-processor.hxx>

#include <libxsd-frontend/semantic-graph.hxx>
#include <libxsd-frontend/traversal.hxx>

using namespace std;

namespace CXX
{
  namespace Tree
  {
    namespace
    {
      struct Member: Traversal::Element, Traversal::Any
      {
        Member (size_t count): count_ (count) {}

        virtual void
        traverse (SemanticGraph::Element& e)
        {
          if (Context::skip (e))
            return;

          e.context ().set ("ordered-id", count_++);
        }

        virtual void
        traverse (SemanticGraph::Any& a)
        {
          a.context ().set ("ordered-id", count_++);
        }

        size_t count_;
      };

      //
      //
      struct Type: Traversal::Complex
      {
        Type (TypeNameSet& ordered_types, bool derived, bool mixed, bool all)
            : ordered_types_ (ordered_types),
              derived_ (derived),
              mixed_ (mixed),
              all_ (all)
        {
        }

        virtual void
        traverse (SemanticGraph::Complex& c)
        {
          SemanticGraph::Context& ctx (c.context ());

          if (!ctx.count ("ordered"))
          {
            // First process our base.
            //
            if (c.inherits_p ())
            {
              SemanticGraph::Type& b (c.inherits ().base ());

              if (!b.context ().count ("ordered"))
                dispatch (b);
            }

            // See if our base (not necessarily immediate) is ordered.
            //
            using SemanticGraph::Complex;

            Complex* b (0);

            for (Complex* p (&c); p->inherits_p ();)
            {
              if ((b = dynamic_cast<Complex*> (&p->inherits ().base ())))
              {
                if (Context::ordered_p (*b))
                  break;

                p = b;
              }
              else
                break;
            }

            bool o (all_ ||
                    (derived_ && b != 0 && Context::ordered_p (*b)) ||
                    (mixed_ && c.mixed_p ()) ||
                    ordered_types_.find (c));
            ctx.set ("ordered", o);

            // Assign ids to elements and wildcards, calculate total count.
            //
            if (o)
            {
              size_t count (
                b != 0 && Context::ordered_p (*b)
                ? b->context ().get<size_t> ("ordered-count")
                : 1);

              ctx.set ("ordered-start", count);

              Member m (count);
              Traversal::Names n (m);
              names (c, n);

              // Assign content id for mixed text.
              //
              if (Context::mixed_p (c) && count == 1)
                ctx.set ("mixed-ordered-id", m.count_++);

              ctx.set ("ordered-count", m.count_);
            }
          }
        }

      private:
        TypeNameSet& ordered_types_;
        bool derived_;
        bool mixed_;
        bool all_;
      };

      // Go into sourced/included/imported schemas while making sure
      // we don't process the same stuff more than once.
      //
      struct Uses: Traversal::Sources,
                   Traversal::Includes,
                   Traversal::Imports
      {
        Uses (char const* seen_key)
            : seen_key_ (seen_key)
        {
        }

        virtual void
        traverse (SemanticGraph::Sources& sr)
        {
          SemanticGraph::Schema& s (sr.schema ());

          if (!s.context ().count (seen_key_))
          {
            s.context ().set (seen_key_, true);
            Traversal::Sources::traverse (sr);
          }
        }

        virtual void
        traverse (SemanticGraph::Includes& i)
        {
          SemanticGraph::Schema& s (i.schema ());

          if (!s.context ().count (seen_key_))
          {
            s.context ().set (seen_key_, true);
            Traversal::Includes::traverse (i);
          }
        }

        virtual void
        traverse (SemanticGraph::Imports& i)
        {
          SemanticGraph::Schema& s (i.schema ());

          if (!s.context ().count (seen_key_))
          {
            s.context ().set (seen_key_, true);
            Traversal::Imports::traverse (i);
          }
        }

      private:
        char const* seen_key_;
      };

      char const* seen_key = "cxx-tree-order-processor-seen";

      bool
      process_impl (options const& ops,
                    SemanticGraph::Schema& tu,
                    SemanticGraph::Path const&)
      {
        // Prepare a set of ordered types.
        //
        TypeNameSet ordered_types (ops.ordered_type ().begin (),
                                   ops.ordered_type ().end ());

        // Root schema in the file-per-type mode is just a bunch
        // of includes without a namespace.
        //
        SemanticGraph::Schema::NamesIterator i (tu.names_begin ());

        // Nothing to do if this is the XML Schema namespace.
        //
        if (i == tu.names_end () ||
            i->named ().name () != L"http://www.w3.org/2001/XMLSchema")
        {
          // Note that we check first if this schema has already been
          // processed which may happen in the file-per-type compilation
          // mode.
          //
          if (!tu.context ().count (seen_key))
          {
            Traversal::Schema schema;
            Uses uses (seen_key);

            schema >> uses >> schema;

            Traversal::Names schema_names;
            Traversal::Namespace ns;
            Traversal::Names ns_names;
            Type type (ordered_types,
                       ops.ordered_type_derived (),
                       ops.ordered_type_mixed (),
                       ops.ordered_type_all ());

            schema >> schema_names >> ns >> ns_names >> type;

            // Some twisted schemas do recusive self-inclusion.
            //
            tu.context ().set (seen_key, true);

            schema.dispatch (tu);
          }
        }

        return true;
      }
    }

    bool OrderProcessor::
    process (options const& ops,
             SemanticGraph::Schema& tu,
             SemanticGraph::Path const& file)
    {
      return process_impl (ops, tu, file);
    }
  }
}

// file      : xsd/cxx/tree/counter.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsd/cxx/tree/counter.hxx>

#include <iostream>

namespace CXX
{
  namespace Tree
  {
    namespace
    {
      struct Member: Traversal::Member
      {
        Member (size_t& complexity)
            : complexity_ (complexity)
        {
        }

        virtual void
        traverse (Type&)
        {
          complexity_++;
        }

        size_t& complexity_;
      };

      struct Any: Traversal::Any, Traversal::AnyAttribute
      {
        Any (size_t& complexity)
            : complexity_ (complexity)
        {
        }

        virtual void
        traverse (SemanticGraph::Any&)
        {
          complexity_++;
        }

        virtual void
        traverse (SemanticGraph::AnyAttribute&)
        {
          complexity_++;
        }

        size_t& complexity_;
      };

      struct TypeBase: Traversal::List,
                       Traversal::Union,
                       Traversal::Enumeration,
                       Traversal::Complex,
                       Context
      {
        TypeBase (Context& c, size_t& complexity)
            : Context (c), complexity_ (complexity)
        {
        }

        virtual void
        traverse (SemanticGraph::List&)
        {
          complexity_++;
        }

        virtual void
        traverse (SemanticGraph::Union&)
        {
          complexity_++;
        }

        virtual void
        traverse (SemanticGraph::Enumeration& e)
        {
          bool string_based (false);
          {
            IsStringBasedType t (string_based);
            t.dispatch (e);
          }

          complexity_ += (string_based ? 1 : 2);
        }

        virtual void
        traverse (SemanticGraph::Complex& c)
        {
          complexity_++; // One for the type itself.

          // Plus some for each member.
          //
          Any any (complexity_);
          Member member (complexity_);
          Traversal::Names names;

          names >> member;

          if (options.generate_wildcard ())
            names >> any;

          Complex::names (c, names);
        }

      private:
        size_t& complexity_;
      };


      //
      //
      struct GlobalType: Traversal::Type, Context

      {
        GlobalType (Context& c, Counts& counts)
            : Context (c), counts_ (counts)
        {
        }

        virtual void
        traverse (SemanticGraph::Type& t)
        {
          counts_.global_types++;

          size_t complexity (0);
          TypeBase type (*this, complexity);
          type.dispatch (t);

          counts_.complexity_total += complexity;
          counts_.complexity.push_back (complexity);
        }

      private:
        Counts& counts_;
      };

      //
      //
      struct GlobalElement: Traversal::Element,
                            GlobalElementBase,
                            Context
      {
        GlobalElement (Context& c, Counts& counts)
            : GlobalElementBase (c),
              Context (c),
              counts_ (counts),
              last_ (0)
        {
        }

        ~GlobalElement ()
        {
          if (last_ != 0)
          {
            last_->context ().set ("last", true);
            count_last ();
          }
        }

        virtual void
        traverse (Type& e)
        {
          // Check if the previous element we saw needs to be generated.
          //
          if (last_ != 0)
            count_last ();

          last_ = &e;

          if (counts_.global_elements == 0)
            e.context ().set ("first", true);

          counts_.global_elements++;
        }

      private:
        void
        count_last ()
        {
          if (generate_p (*last_))
          {
            counts_.generated_global_elements++;

            size_t complexity (0);

            if (doc_root_p (*last_))
            {
              if (options.generate_element_type ())
              {
                complexity += 1; // For c-tors and d-tor.

                if (!options.suppress_parsing ())
                  complexity += 1;

                if (options.generate_serialization ())
                  complexity += 1;
              }
              else
              {
                if (!options.suppress_parsing ())
                  complexity += 6; // 13 parsing functions.

                if (options.generate_serialization ())
                  complexity += 4; // 8 serialization functions.
              }
            }

            if (complexity == 0)
            {
              // This element must be a substitution group members. For
              // such elements we are only generating an entry in a map.
              // We will assign it a complexity of 1 so that we don't
              // end up with the total complexity that is less than the
              // number of elements and types.
              //
              complexity = 1;
            }

            counts_.complexity_total += complexity;
            counts_.complexity.push_back (complexity);
          }
        }

      private:
        Counts& counts_;
        SemanticGraph::Element* last_;
      };
    }

    Counts Counter::
    count (options const& ops,
           SemanticGraph::Schema& tu,
           SemanticGraph::Path const& path)
    {
      Counts counts;
      Context ctx (std::wcerr, tu, path, ops, counts, false, 0, 0, 0, 0);

      Traversal::Schema schema;
      Sources sources;

      schema >> sources >> schema;

      {
        Traversal::Names schema_names;
        Traversal::Namespace ns;
        Traversal::Names ns_names;
        GlobalType global_type (ctx, counts);
        GlobalElement global_element (ctx, counts);

        schema >> schema_names >> ns >> ns_names;

        ns_names >> global_element;
        ns_names >> global_type;

        schema.dispatch (tu);
      }

      return counts;
    }
  }
}

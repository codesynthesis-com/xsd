// file      : xsd/elements.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef ELEMENTS_HXX
#define ELEMENTS_HXX

#include <xsd-frontend/semantic-graph.hxx>
#include <xsd-frontend/traversal.hxx>

#include <types.hxx>

namespace SemanticGraph = XSDFrontend::SemanticGraph;
namespace Traversal = XSDFrontend::Traversal;

// Anonymous feedback via belongs edge.
//
struct AnonymousBase : Traversal::Element, Traversal::Attribute
{
  AnonymousBase (Traversal::NodeDispatcher& d1)
      : complex_ (&d1, 0)
  {
    edge_traverser (belongs_);
    belongs_.node_traverser (complex_);
  }

  AnonymousBase (Traversal::NodeDispatcher& d1, Traversal::NodeDispatcher& d2)
      : complex_ (&d1, &d2)
  {
    edge_traverser (belongs_);
    belongs_.node_traverser (complex_);
  }

  // Hooks.
  //
public:
  virtual void
  member_pre (SemanticGraph::Member&)
  {
  }

  virtual void
  member_post (SemanticGraph::Member&)
  {
  }

  /*
    virtual void
    type_pre (SemanticGraph::Type& t)
    {
    }

    virtual void
    type_post (SemanticGraph::Type& t)
    {
    }
  */

public:

  virtual void
  traverse (SemanticGraph::Element& e)
  {
    SemanticGraph::Type& t (e.type ());

    if (!t.named_p () && !t.context ().count ("seen"))
    {
      t.context ().set ("seen", true);

      member_pre (e);

      Element::belongs (e, belongs_);

      member_post (e);

      t.context ().remove ("seen");
    }
  }

  virtual void
  traverse (SemanticGraph::Attribute& a)
  {
    SemanticGraph::Type& t (a.type ());

    if (!t.named_p () && !t.context ().count ("seen"))
    {
      t.context ().set ("seen", true);

      member_pre (a);

      Attribute::belongs (a, belongs_);

      member_post (a);

      t.context ().remove ("seen");
    }
  }

private:
  struct Complex : Traversal::Complex
  {
    Complex (Traversal::NodeDispatcher* d1, Traversal::NodeDispatcher* d2)
        : d1_ (d1), d2_ (d2)
    {
    }

    virtual void
    traverse (SemanticGraph::Complex& c)
    {
      if (d1_)
        d1_->dispatch (c);

      if (d2_)
        d2_->dispatch (c);
    }

  private:
    Traversal::NodeDispatcher* d1_;
    Traversal::NodeDispatcher* d2_;

  } complex_;

  Traversal::Belongs belongs_;
};

#endif // ELEMENTS_HXX

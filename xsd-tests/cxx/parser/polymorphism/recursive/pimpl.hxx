// file      : cxx/parser/polymorphism/recursive/pimpl.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef TEST_PIMPL_HXX
#define TEST_PIMPL_HXX

#include "test-pskel.hxx"

namespace test
{
  class root_pimpl: public virtual root_pskel
  {
  public:
    virtual void
    pre ();

    virtual void
    expression ();

    virtual void
    post_root ();
  };

  class expression_pimpl: public virtual expression_pskel
  {
  public:
    virtual void
    pre ();

    virtual void
    post_expression ();
  };

  class recursive_pimpl: public virtual recursive_pskel,
                         public expression_pimpl
  {
  public:
    virtual void
    pre ();

    virtual void
    expression ();

    virtual void
    post_expression ();

    virtual void
    post_recursive ();
  };

  class value_pimpl: public virtual value_pskel, public expression_pimpl
  {
  public:
    virtual void
    pre ();

    virtual void
    constant (int);

    virtual void
    post_expression ();

    virtual void
    post_value ();
  };

  class value_a_pimpl: public virtual value_a_pskel, public value_pimpl
  {
  public:
    virtual void
    pre ();

    virtual void
    post_value ();

    virtual void
    post_value_a ();
  };

  class value_b_pimpl: public virtual value_b_pskel, public value_pimpl
  {
  public:
    virtual void
    pre ();

    virtual void
    post_value ();

    virtual void
    post_value_b ();
  };
}

#endif // TEST_PIMPL_HXX

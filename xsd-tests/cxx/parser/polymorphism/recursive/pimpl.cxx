// file      : cxx/parser/polymorphism/recursive/pimpl.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <iostream>

#include "pimpl.hxx"

using namespace std;

namespace test
{
  // root_pimpl
  //

  void root_pimpl::
  pre ()
  {
    cout << "root start" << endl;
  }

  void root_pimpl::
  expression ()
  {
    cout << "root->expression" << endl;
  }

  void root_pimpl::
  post_root ()
  {
    cout << "root end" << endl;
  }

  // expression_pimpl
  //

  void expression_pimpl::
  pre ()
  {
    cout << "expression begin" << endl;
  }

  void expression_pimpl::
  post_expression ()
  {
    cout << "expression end" << endl;
  }

  // recursive_pimpl
  //

  void recursive_pimpl::
  pre ()
  {
    cout << "recursive start" << endl;
  }

  void recursive_pimpl::
  expression ()
  {
    cout << "recursive->expression event" << endl;
  }

  void recursive_pimpl::
  post_expression ()
  {
    cout << "recursive: post_expression override" << endl;
    post_recursive ();
  }

  void recursive_pimpl::
  post_recursive ()
  {
    cout << "recursive end" << endl;
  }

  // value_pimpl
  //

  void value_pimpl::
  pre ()
  {
    cout << "value begin" << endl;
  }

  void value_pimpl::
  constant (int)
  {
    cout << "value->constant" << endl;
  }

  void value_pimpl::
  post_expression ()
  {
    cout << "value: post_expression override" << endl;
    post_value ();
  }

  void value_pimpl::
  post_value ()
  {
    cout << "value end" << endl;
  }

  // value_a_pimpl
  //

  void value_a_pimpl::
  pre ()
  {
    cout << "value_a begin" << endl;
  }

  void value_a_pimpl::
  post_value ()
  {
    cout << "value_a: post_value override" << endl;
    post_value_a ();
  }

  void value_a_pimpl::
  post_value_a ()
  {
    cout << "value_a end" << endl;
  }

  // value_b_pimpl
  //

  void value_b_pimpl::
  pre ()
  {
    cout << "value_b begin" << endl;
  }

  void value_b_pimpl::
  post_value ()
  {
    cout << "value_b: post_value override" << endl;
    post_value_b ();
  }

  void value_b_pimpl::
  post_value_b ()
  {
    cout << "value_b end" << endl;
  }
}

// file      : cxx/tree/union/ctor/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test union constructors.
//
#include <string>

#include "test.hxx"

#undef NDEBUG
#include <cassert>

using namespace std;
using namespace test;

int
main ()
{
  // Test ctor(const std::string&)
  //
  {
    string const s ("123");
    int_string_union u (s);
    type t (s);
  }

  // Test ctor(const char*).
  //
  {
    int_string_union u ("123");
    type t ("123");
  }
}

// file      : cxx/tree/enumeration/ctor/driver.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

// Test enumeration constructors.
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
  // Test ctor(const char*).
  //
  {
    string_enum se ("a");
    type t ("a", 1);
  }

  // Test ctor(const std::string&)
  //
  {
    string const s ("c");
    string_enum se (s);
    type t (s, 3);
  }
}

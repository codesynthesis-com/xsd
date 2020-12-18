// file      : xsd/cxx/option-types.cxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <istream>
#include <ostream>

#include <xsd/cxx/option-types.hxx>

using namespace std;

namespace CXX
{
  //
  // cxx_version
  //

  static const char* cxx_version_[] =
  {
    "c++98",
    "c++11"
  };

  string cxx_version::
  string () const
  {
    return cxx_version_[v_];
  }

  istream&
  operator>> (istream& is, cxx_version& v)
  {
    string s;
    is >> s;

    if (!is.fail ())
    {
      if (s == "c++98")
        v = cxx_version::cxx98;
      else if (s == "c++11")
        v = cxx_version::cxx11;
      else
        is.setstate (istream::failbit);
    }

    return is;
  }
}

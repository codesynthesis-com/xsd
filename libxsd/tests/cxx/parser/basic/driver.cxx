// file      : tests/cxx/parser/xerces/basic/driver.cxx
// copyright : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <cassert>
#include <iostream>

// Define XSD_CXX11 since we include libxsd headers directly.
//
#ifdef _MSC_VER
#  if _MSC_VER >= 1600 // VC++10 and later have C++11 always enabled.
#    define XSD_CXX11
#  endif
#else
#  if defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L
#    define XSD_CXX11
#  endif
#endif

#include <libxsd/cxx/config.hxx>    // XSD_UNUSED
#include <libxsd/cxx/ro-string.hxx>

#ifdef PARSER_EXPAT
#  include <libxsd/cxx/parser/expat/elements.hxx>
#else
#  include <libxsd/cxx/parser/xerces/elements.hxx>
#endif

#include <libxsd/cxx/parser/non-validating/parser.hxx>
#include <libxsd/cxx/parser/non-validating/xml-schema-pskel.hxx>
#include <libxsd/cxx/parser/non-validating/xml-schema-pimpl.hxx>

using namespace std;
using namespace xsd::cxx;

typedef parser::non_validating::string_pskel<char> string_pskel;

class hello_pimpl: public parser::non_validating::complex_content<char>
{
public:
  hello_pimpl (string_pskel& greeting, string_pskel& name)
      : greeting_parser_ (&greeting),
        name_parser_ (&name) {}

private:
  virtual bool
  _start_element_impl (const ro_string<char>&,
                       const ro_string<char>&,
                       const ro_string<char>*);

  virtual bool
  _end_element_impl (const ro_string<char>&, const ro_string<char>&);

  string_pskel* greeting_parser_;
  string_pskel* name_parser_;
};

bool hello_pimpl::
_start_element_impl (const ro_string<char>& ns,
                     const ro_string<char>& n,
                     const ro_string<char>* t)
{
  XSD_UNUSED (t);

  if (complex_content::_start_element_impl (ns, n, t))
    return true;

  if (n == "greeting" && ns.empty ())
  {
    context_.top ().parser_ = greeting_parser_;

    if (greeting_parser_)
      greeting_parser_->pre ();

    return true;
  }

  if (n == "name" && ns.empty ())
  {
    context_.top ().parser_ = name_parser_;

    if (name_parser_)
      name_parser_->pre ();

    return true;
  }

  return false;
}

bool hello_pimpl::
_end_element_impl (const ro_string<char>& ns, const ro_string<char>& n)
{
  if (complex_content::_end_element_impl (ns, n))
    return true;

  if (n == "greeting" && ns.empty ())
  {
    cout << n << ' ' << greeting_parser_->post_string () << endl;
    return true;
  }

  if (n == "name" && ns.empty ())
  {
    cout << n << ' ' << name_parser_->post_string () << endl;
    return true;
  }

  return false;
}


int
main (int argc, char* argv[])
{
  assert (argc == 2);

  parser::non_validating::string_pimpl<char> string_p;
  hello_pimpl hello_p (string_p, string_p);

#ifdef PARSER_EXPAT
  parser::expat::document<char>  doc_p (hello_p, "hello");
#else
  parser::xerces::document<char> doc_p (hello_p, "hello");
#endif

  doc_p.parse (argv[1]);
}

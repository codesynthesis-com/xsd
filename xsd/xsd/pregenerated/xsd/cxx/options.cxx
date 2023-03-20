// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

// Begin prologue.
//
#include <xsd/options-parser.hxx>
//
// End prologue.

#include <xsd/cxx/options.hxx>

#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <ostream>
#include <sstream>
#include <cstring>

namespace cli
{
  template <typename X>
  struct parser
  {
    static void
    parse (X& x, bool& xs, scanner& s)
    {
      using namespace std;

      const char* o (s.next ());
      if (s.more ())
      {
        string v (s.next ());
        istringstream is (v);
        if (!(is >> x && is.peek () == istringstream::traits_type::eof ()))
          throw invalid_value (o, v);
      }
      else
        throw missing_value (o);

      xs = true;
    }
  };

  template <>
  struct parser<bool>
  {
    static void
    parse (bool& x, bool& xs, scanner& s)
    {
      const char* o (s.next ());

      if (s.more ())
      {
        const char* v (s.next ());

        if (std::strcmp (v, "1")    == 0 ||
            std::strcmp (v, "true") == 0 ||
            std::strcmp (v, "TRUE") == 0 ||
            std::strcmp (v, "True") == 0)
          x = true;
        else if (std::strcmp (v, "0")     == 0 ||
                 std::strcmp (v, "false") == 0 ||
                 std::strcmp (v, "FALSE") == 0 ||
                 std::strcmp (v, "False") == 0)
          x = false;
        else
          throw invalid_value (o, v);
      }
      else
        throw missing_value (o);

      xs = true;
    }
  };

  template <>
  struct parser<std::string>
  {
    static void
    parse (std::string& x, bool& xs, scanner& s)
    {
      const char* o (s.next ());

      if (s.more ())
        x = s.next ();
      else
        throw missing_value (o);

      xs = true;
    }
  };

  template <typename X>
  struct parser<std::pair<X, std::size_t> >
  {
    static void
    parse (std::pair<X, std::size_t>& x, bool& xs, scanner& s)
    {
      x.second = s.position ();
      parser<X>::parse (x.first, xs, s);
    }
  };

  template <typename X>
  struct parser<std::vector<X> >
  {
    static void
    parse (std::vector<X>& c, bool& xs, scanner& s)
    {
      X x;
      bool dummy;
      parser<X>::parse (x, dummy, s);
      c.push_back (x);
      xs = true;
    }
  };

  template <typename X, typename C>
  struct parser<std::set<X, C> >
  {
    static void
    parse (std::set<X, C>& c, bool& xs, scanner& s)
    {
      X x;
      bool dummy;
      parser<X>::parse (x, dummy, s);
      c.insert (x);
      xs = true;
    }
  };

  template <typename K, typename V, typename C>
  struct parser<std::map<K, V, C> >
  {
    static void
    parse (std::map<K, V, C>& m, bool& xs, scanner& s)
    {
      const char* o (s.next ());

      if (s.more ())
      {
        std::size_t pos (s.position ());
        std::string ov (s.next ());
        std::string::size_type p = ov.find ('=');

        K k = K ();
        V v = V ();
        std::string kstr (ov, 0, p);
        std::string vstr (ov, (p != std::string::npos ? p + 1 : ov.size ()));

        int ac (2);
        char* av[] =
        {
          const_cast<char*> (o),
          0
        };

        bool dummy;
        if (!kstr.empty ())
        {
          av[1] = const_cast<char*> (kstr.c_str ());
          argv_scanner s (0, ac, av, false, pos);
          parser<K>::parse (k, dummy, s);
        }

        if (!vstr.empty ())
        {
          av[1] = const_cast<char*> (vstr.c_str ());
          argv_scanner s (0, ac, av, false, pos);
          parser<V>::parse (v, dummy, s);
        }

        m[k] = v;
      }
      else
        throw missing_value (o);

      xs = true;
    }
  };

  template <typename K, typename V, typename C>
  struct parser<std::multimap<K, V, C> >
  {
    static void
    parse (std::multimap<K, V, C>& m, bool& xs, scanner& s)
    {
      const char* o (s.next ());

      if (s.more ())
      {
        std::size_t pos (s.position ());
        std::string ov (s.next ());
        std::string::size_type p = ov.find ('=');

        K k = K ();
        V v = V ();
        std::string kstr (ov, 0, p);
        std::string vstr (ov, (p != std::string::npos ? p + 1 : ov.size ()));

        int ac (2);
        char* av[] =
        {
          const_cast<char*> (o),
          0
        };

        bool dummy;
        if (!kstr.empty ())
        {
          av[1] = const_cast<char*> (kstr.c_str ());
          argv_scanner s (0, ac, av, false, pos);
          parser<K>::parse (k, dummy, s);
        }

        if (!vstr.empty ())
        {
          av[1] = const_cast<char*> (vstr.c_str ());
          argv_scanner s (0, ac, av, false, pos);
          parser<V>::parse (v, dummy, s);
        }

        m.insert (typename std::multimap<K, V, C>::value_type (k, v));
      }
      else
        throw missing_value (o);

      xs = true;
    }
  };

  template <typename X, typename T, T X::*M>
  void
  thunk (X& x, scanner& s)
  {
    parser<T>::parse (x.*M, s);
  }

  template <typename X, bool X::*M>
  void
  thunk (X& x, scanner& s)
  {
    s.next ();
    x.*M = true;
  }

  template <typename X, typename T, T X::*M, bool X::*S>
  void
  thunk (X& x, scanner& s)
  {
    parser<T>::parse (x.*M, x.*S, s);
  }
}

#include <map>

namespace CXX
{
  // options
  //

  options::
  options ()
  : std_ (cxx_version::cxx98),
    std_specified_ (false),
    char_type_ ("char"),
    char_type_specified_ (false),
    char_encoding_ (),
    char_encoding_specified_ (false),
    output_dir_ (),
    output_dir_specified_ (false),
    generate_inline_ (),
    generate_xml_schema_ (),
    extern_xml_schema_ (),
    extern_xml_schema_specified_ (false),
    namespace_map_ (),
    namespace_map_specified_ (false),
    namespace_regex_ (),
    namespace_regex_specified_ (false),
    namespace_regex_trace_ (),
    reserved_name_ (),
    reserved_name_specified_ (false),
    include_with_brackets_ (),
    include_prefix_ (),
    include_prefix_specified_ (false),
    include_regex_ (),
    include_regex_specified_ (false),
    include_regex_trace_ (),
    guard_prefix_ (),
    guard_prefix_specified_ (false),
    hxx_suffix_ (".hxx"),
    hxx_suffix_specified_ (false),
    ixx_suffix_ (".ixx"),
    ixx_suffix_specified_ (false),
    cxx_suffix_ (".cxx"),
    cxx_suffix_specified_ (false),
    fwd_suffix_ ("-fwd.hxx"),
    fwd_suffix_specified_ (false),
    hxx_regex_ (),
    hxx_regex_specified_ (false),
    ixx_regex_ (),
    ixx_regex_specified_ (false),
    cxx_regex_ (),
    cxx_regex_specified_ (false),
    fwd_regex_ (),
    fwd_regex_specified_ (false),
    hxx_prologue_ (),
    hxx_prologue_specified_ (false),
    ixx_prologue_ (),
    ixx_prologue_specified_ (false),
    cxx_prologue_ (),
    cxx_prologue_specified_ (false),
    fwd_prologue_ (),
    fwd_prologue_specified_ (false),
    prologue_ (),
    prologue_specified_ (false),
    hxx_epilogue_ (),
    hxx_epilogue_specified_ (false),
    ixx_epilogue_ (),
    ixx_epilogue_specified_ (false),
    cxx_epilogue_ (),
    cxx_epilogue_specified_ (false),
    fwd_epilogue_ (),
    fwd_epilogue_specified_ (false),
    epilogue_ (),
    epilogue_specified_ (false),
    hxx_prologue_file_ (),
    hxx_prologue_file_specified_ (false),
    ixx_prologue_file_ (),
    ixx_prologue_file_specified_ (false),
    cxx_prologue_file_ (),
    cxx_prologue_file_specified_ (false),
    fwd_prologue_file_ (),
    fwd_prologue_file_specified_ (false),
    prologue_file_ (),
    prologue_file_specified_ (false),
    hxx_epilogue_file_ (),
    hxx_epilogue_file_specified_ (false),
    ixx_epilogue_file_ (),
    ixx_epilogue_file_specified_ (false),
    cxx_epilogue_file_ (),
    cxx_epilogue_file_specified_ (false),
    fwd_epilogue_file_ (),
    fwd_epilogue_file_specified_ (false),
    epilogue_file_ (),
    epilogue_file_specified_ (false),
    export_symbol_ (),
    export_symbol_specified_ (false),
    export_xml_schema_ (),
    export_maps_ (),
    import_maps_ (),
    generate_dep_ (),
    generate_dep_only_ (),
    dep_phony_ (),
    dep_target_ (),
    dep_target_specified_ (false),
    dep_suffix_ (".d"),
    dep_suffix_specified_ (false),
    dep_regex_ (),
    dep_regex_specified_ (false)
  {
  }

  ::cli::usage_para options::
  print_usage (::std::wostream& os, ::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    if (p == ::cli::usage_para::text)
      os << ::std::endl;

    os << "--std <version>              Specify the C++ standard that the generated code" << ::std::endl
       << "                             should conform to." << ::std::endl;

    os << "--char-type <type>           Generate code using the provided character <type>" << ::std::endl
       << "                             instead of the default char." << ::std::endl;

    os << "--char-encoding <enc>        Specify the character encoding that should be used" << ::std::endl
       << "                             in the generated code." << ::std::endl;

    os << "--output-dir <dir>           Write generated files to <dir> instead of the" << ::std::endl
       << "                             current directory." << ::std::endl;

    os << "--generate-inline            Generate simple functions inline." << ::std::endl;

    os << "--generate-xml-schema        Generate a C++ header file as if the schema being" << ::std::endl
       << "                             compiled defines the XML Schema namespace." << ::std::endl;

    os << "--extern-xml-schema <file>   Include a header file derived from <file> instead" << ::std::endl
       << "                             of generating the XML Schema namespace mapping" << ::std::endl
       << "                             inline." << ::std::endl;

    os << "--namespace-map <xns>=<cns>  Map XML Schema namespace <xns> to C++ namespace" << ::std::endl
       << "                             <cns>." << ::std::endl;

    os << "--namespace-regex <regex>    Add <regex> to the list of regular expressions" << ::std::endl
       << "                             used to translate XML Schema namespace names to" << ::std::endl
       << "                             C++ namespace names." << ::std::endl;

    os << "--namespace-regex-trace      Trace the process of applying regular expressions" << ::std::endl
       << "                             specified with the --namespace-regex option." << ::std::endl;

    os << "--reserved-name <n>[=<r>]    Add name <n> to the list of names that should not" << ::std::endl
       << "                             be used as identifiers." << ::std::endl;

    os << "--include-with-brackets      Use angle brackets (<>) instead of quotes (\"\") in" << ::std::endl
       << "                             generated #include directives." << ::std::endl;

    os << "--include-prefix <prefix>    Add <prefix> to generated #include directive" << ::std::endl
       << "                             paths." << ::std::endl;

    os << "--include-regex <regex>      Add <regex> to the list of regular expressions" << ::std::endl
       << "                             used to transform #include directive paths." << ::std::endl;

    os << "--include-regex-trace        Trace the process of applying regular expressions" << ::std::endl
       << "                             specified with the --include-regex option." << ::std::endl;

    os << "--guard-prefix <prefix>      Add <prefix> to generated header inclusion guards." << ::std::endl;

    os << "--hxx-suffix <suffix>        Use the provided <suffix> instead of the default" << ::std::endl
       << "                             .hxx to construct the name of the header file." << ::std::endl;

    os << "--ixx-suffix <suffix>        Use the provided <suffix> instead of the default" << ::std::endl
       << "                             .ixx to construct the name of the inline file." << ::std::endl;

    os << "--cxx-suffix <suffix>        Use the provided <suffix> instead of the default" << ::std::endl
       << "                             .cxx to construct the name of the source file." << ::std::endl;

    os << "--fwd-suffix <suffix>        Use the provided <suffix> instead of the default" << ::std::endl
       << "                             -fwd.hxx to construct the name of the forward" << ::std::endl
       << "                             declaration file." << ::std::endl;

    os << "--hxx-regex <regex>          Use the provided expression to construct the name" << ::std::endl
       << "                             of the header file." << ::std::endl;

    os << "--ixx-regex <regex>          Use the provided expression to construct the name" << ::std::endl
       << "                             of the inline file." << ::std::endl;

    os << "--cxx-regex <regex>          Use the provided expression to construct the name" << ::std::endl
       << "                             of the source file." << ::std::endl;

    os << "--fwd-regex <regex>          Use the provided expression to construct the name" << ::std::endl
       << "                             of the forward declaration file." << ::std::endl;

    os << "--hxx-prologue <text>        Insert <text> at the beginning of the header file." << ::std::endl;

    os << "--ixx-prologue <text>        Insert <text> at the beginning of the inline file." << ::std::endl;

    os << "--cxx-prologue <text>        Insert <text> at the beginning of the source file." << ::std::endl;

    os << "--fwd-prologue <text>        Insert <text> at the beginning of the forward" << ::std::endl
       << "                             declaration file." << ::std::endl;

    os << "--prologue <text>            Insert <text> at the beginning of each generated" << ::std::endl
       << "                             file for which there is no file-specific prologue." << ::std::endl;

    os << "--hxx-epilogue <text>        Insert <text> at the end of the header file." << ::std::endl;

    os << "--ixx-epilogue <text>        Insert <text> at the end of the inline file." << ::std::endl;

    os << "--cxx-epilogue <text>        Insert <text> at the end of the source file." << ::std::endl;

    os << "--fwd-epilogue <text>        Insert <text> at the end of the forward" << ::std::endl
       << "                             declaration file." << ::std::endl;

    os << "--epilogue <text>            Insert <text> at the end of each generated file" << ::std::endl
       << "                             for which there is no file-specific epilogue." << ::std::endl;

    os << "--hxx-prologue-file <file>   Insert the content of the <file> at the beginning" << ::std::endl
       << "                             of the header file." << ::std::endl;

    os << "--ixx-prologue-file <file>   Insert the content of the <file> at the beginning" << ::std::endl
       << "                             of the inline file." << ::std::endl;

    os << "--cxx-prologue-file <file>   Insert the content of the <file> at the beginning" << ::std::endl
       << "                             of the source file." << ::std::endl;

    os << "--fwd-prologue-file <file>   Insert the content of the <file> at the beginning" << ::std::endl
       << "                             of the forward declaration file." << ::std::endl;

    os << "--prologue-file <file>       Insert the content of the <file> at the beginning" << ::std::endl
       << "                             of each generated file for which there is no" << ::std::endl
       << "                             file-specific prologue file." << ::std::endl;

    os << "--hxx-epilogue-file <file>   Insert the content of the <file> at the end of the" << ::std::endl
       << "                             header file." << ::std::endl;

    os << "--ixx-epilogue-file <file>   Insert the content of the <file> at the end of the" << ::std::endl
       << "                             inline file." << ::std::endl;

    os << "--cxx-epilogue-file <file>   Insert the content of the <file> at the end of the" << ::std::endl
       << "                             source file." << ::std::endl;

    os << "--fwd-epilogue-file <file>   Insert the content of the <file> at the end of the" << ::std::endl
       << "                             forward declaration file." << ::std::endl;

    os << "--epilogue-file <file>       Insert the content of the <file> at the end of" << ::std::endl
       << "                             each generated file for which there is no" << ::std::endl
       << "                             file-specific epilogue file." << ::std::endl;

    os << "--export-symbol <symbol>     Insert <symbol> in places where DLL export/import" << ::std::endl
       << "                             control statements" << ::std::endl
       << "                             (__declspec(dllexport/dllimport)) are necessary." << ::std::endl;

    os << "--export-xml-schema          Export/import types in the XML Schema namespace" << ::std::endl
       << "                             using the export symbol provided with the" << ::std::endl
       << "                             --export-symbol option." << ::std::endl;

    os << "--export-maps                Export polymorphism support maps from a Win32 DLL" << ::std::endl
       << "                             into which this generated code is placed." << ::std::endl;

    os << "--import-maps                Import polymorphism support maps to a Win32 DLL or" << ::std::endl
       << "                             executable into which this generated code is" << ::std::endl
       << "                             linked." << ::std::endl;

    os << "--generate-dep               Generate make dependency information." << ::std::endl;

    os << "--generate-dep-only          Generate make dependency information only." << ::std::endl;

    os << "--dep-phony                  Generate phony targets for included/imported" << ::std::endl
       << "                             schema files, causing each to depend on nothing." << ::std::endl;

    os << "--dep-target <target>        Change the target of the dependency rule." << ::std::endl;

    os << "--dep-suffix <suffix>        Use the provided <suffix> instead of the default" << ::std::endl
       << "                             .d to construct the name of the dependency file." << ::std::endl;

    os << "--dep-regex <regex>          Use the provided expression to construct the name" << ::std::endl
       << "                             of the dependency file." << ::std::endl;

    p = ::cli::usage_para::option;

    return p;
  }

  typedef
  std::map<std::string, void (*) (options&, ::cli::scanner&)>
  _cli_options_map;

  static _cli_options_map _cli_options_map_;

  struct _cli_options_map_init
  {
    _cli_options_map_init ()
    {
      _cli_options_map_["--std"] =
      &::cli::thunk< options, cxx_version, &options::std_,
        &options::std_specified_ >;
      _cli_options_map_["--char-type"] =
      &::cli::thunk< options, NarrowString, &options::char_type_,
        &options::char_type_specified_ >;
      _cli_options_map_["--char-encoding"] =
      &::cli::thunk< options, NarrowString, &options::char_encoding_,
        &options::char_encoding_specified_ >;
      _cli_options_map_["--output-dir"] =
      &::cli::thunk< options, NarrowString, &options::output_dir_,
        &options::output_dir_specified_ >;
      _cli_options_map_["--generate-inline"] =
      &::cli::thunk< options, &options::generate_inline_ >;
      _cli_options_map_["--generate-xml-schema"] =
      &::cli::thunk< options, &options::generate_xml_schema_ >;
      _cli_options_map_["--extern-xml-schema"] =
      &::cli::thunk< options, NarrowString, &options::extern_xml_schema_,
        &options::extern_xml_schema_specified_ >;
      _cli_options_map_["--namespace-map"] =
      &::cli::thunk< options, NarrowStrings, &options::namespace_map_,
        &options::namespace_map_specified_ >;
      _cli_options_map_["--namespace-regex"] =
      &::cli::thunk< options, NarrowStrings, &options::namespace_regex_,
        &options::namespace_regex_specified_ >;
      _cli_options_map_["--namespace-regex-trace"] =
      &::cli::thunk< options, &options::namespace_regex_trace_ >;
      _cli_options_map_["--reserved-name"] =
      &::cli::thunk< options, NarrowStrings, &options::reserved_name_,
        &options::reserved_name_specified_ >;
      _cli_options_map_["--include-with-brackets"] =
      &::cli::thunk< options, &options::include_with_brackets_ >;
      _cli_options_map_["--include-prefix"] =
      &::cli::thunk< options, NarrowString, &options::include_prefix_,
        &options::include_prefix_specified_ >;
      _cli_options_map_["--include-regex"] =
      &::cli::thunk< options, NarrowStrings, &options::include_regex_,
        &options::include_regex_specified_ >;
      _cli_options_map_["--include-regex-trace"] =
      &::cli::thunk< options, &options::include_regex_trace_ >;
      _cli_options_map_["--guard-prefix"] =
      &::cli::thunk< options, NarrowString, &options::guard_prefix_,
        &options::guard_prefix_specified_ >;
      _cli_options_map_["--hxx-suffix"] =
      &::cli::thunk< options, NarrowString, &options::hxx_suffix_,
        &options::hxx_suffix_specified_ >;
      _cli_options_map_["--ixx-suffix"] =
      &::cli::thunk< options, NarrowString, &options::ixx_suffix_,
        &options::ixx_suffix_specified_ >;
      _cli_options_map_["--cxx-suffix"] =
      &::cli::thunk< options, NarrowString, &options::cxx_suffix_,
        &options::cxx_suffix_specified_ >;
      _cli_options_map_["--fwd-suffix"] =
      &::cli::thunk< options, NarrowString, &options::fwd_suffix_,
        &options::fwd_suffix_specified_ >;
      _cli_options_map_["--hxx-regex"] =
      &::cli::thunk< options, NarrowString, &options::hxx_regex_,
        &options::hxx_regex_specified_ >;
      _cli_options_map_["--ixx-regex"] =
      &::cli::thunk< options, NarrowString, &options::ixx_regex_,
        &options::ixx_regex_specified_ >;
      _cli_options_map_["--cxx-regex"] =
      &::cli::thunk< options, NarrowString, &options::cxx_regex_,
        &options::cxx_regex_specified_ >;
      _cli_options_map_["--fwd-regex"] =
      &::cli::thunk< options, NarrowString, &options::fwd_regex_,
        &options::fwd_regex_specified_ >;
      _cli_options_map_["--hxx-prologue"] =
      &::cli::thunk< options, NarrowStrings, &options::hxx_prologue_,
        &options::hxx_prologue_specified_ >;
      _cli_options_map_["--ixx-prologue"] =
      &::cli::thunk< options, NarrowStrings, &options::ixx_prologue_,
        &options::ixx_prologue_specified_ >;
      _cli_options_map_["--cxx-prologue"] =
      &::cli::thunk< options, NarrowStrings, &options::cxx_prologue_,
        &options::cxx_prologue_specified_ >;
      _cli_options_map_["--fwd-prologue"] =
      &::cli::thunk< options, NarrowStrings, &options::fwd_prologue_,
        &options::fwd_prologue_specified_ >;
      _cli_options_map_["--prologue"] =
      &::cli::thunk< options, NarrowStrings, &options::prologue_,
        &options::prologue_specified_ >;
      _cli_options_map_["--hxx-epilogue"] =
      &::cli::thunk< options, NarrowStrings, &options::hxx_epilogue_,
        &options::hxx_epilogue_specified_ >;
      _cli_options_map_["--ixx-epilogue"] =
      &::cli::thunk< options, NarrowStrings, &options::ixx_epilogue_,
        &options::ixx_epilogue_specified_ >;
      _cli_options_map_["--cxx-epilogue"] =
      &::cli::thunk< options, NarrowStrings, &options::cxx_epilogue_,
        &options::cxx_epilogue_specified_ >;
      _cli_options_map_["--fwd-epilogue"] =
      &::cli::thunk< options, NarrowStrings, &options::fwd_epilogue_,
        &options::fwd_epilogue_specified_ >;
      _cli_options_map_["--epilogue"] =
      &::cli::thunk< options, NarrowStrings, &options::epilogue_,
        &options::epilogue_specified_ >;
      _cli_options_map_["--hxx-prologue-file"] =
      &::cli::thunk< options, NarrowString, &options::hxx_prologue_file_,
        &options::hxx_prologue_file_specified_ >;
      _cli_options_map_["--ixx-prologue-file"] =
      &::cli::thunk< options, NarrowString, &options::ixx_prologue_file_,
        &options::ixx_prologue_file_specified_ >;
      _cli_options_map_["--cxx-prologue-file"] =
      &::cli::thunk< options, NarrowString, &options::cxx_prologue_file_,
        &options::cxx_prologue_file_specified_ >;
      _cli_options_map_["--fwd-prologue-file"] =
      &::cli::thunk< options, NarrowString, &options::fwd_prologue_file_,
        &options::fwd_prologue_file_specified_ >;
      _cli_options_map_["--prologue-file"] =
      &::cli::thunk< options, NarrowString, &options::prologue_file_,
        &options::prologue_file_specified_ >;
      _cli_options_map_["--hxx-epilogue-file"] =
      &::cli::thunk< options, NarrowString, &options::hxx_epilogue_file_,
        &options::hxx_epilogue_file_specified_ >;
      _cli_options_map_["--ixx-epilogue-file"] =
      &::cli::thunk< options, NarrowString, &options::ixx_epilogue_file_,
        &options::ixx_epilogue_file_specified_ >;
      _cli_options_map_["--cxx-epilogue-file"] =
      &::cli::thunk< options, NarrowString, &options::cxx_epilogue_file_,
        &options::cxx_epilogue_file_specified_ >;
      _cli_options_map_["--fwd-epilogue-file"] =
      &::cli::thunk< options, NarrowString, &options::fwd_epilogue_file_,
        &options::fwd_epilogue_file_specified_ >;
      _cli_options_map_["--epilogue-file"] =
      &::cli::thunk< options, NarrowString, &options::epilogue_file_,
        &options::epilogue_file_specified_ >;
      _cli_options_map_["--export-symbol"] =
      &::cli::thunk< options, NarrowString, &options::export_symbol_,
        &options::export_symbol_specified_ >;
      _cli_options_map_["--export-xml-schema"] =
      &::cli::thunk< options, &options::export_xml_schema_ >;
      _cli_options_map_["--export-maps"] =
      &::cli::thunk< options, &options::export_maps_ >;
      _cli_options_map_["--import-maps"] =
      &::cli::thunk< options, &options::import_maps_ >;
      _cli_options_map_["--generate-dep"] =
      &::cli::thunk< options, &options::generate_dep_ >;
      _cli_options_map_["--generate-dep-only"] =
      &::cli::thunk< options, &options::generate_dep_only_ >;
      _cli_options_map_["--dep-phony"] =
      &::cli::thunk< options, &options::dep_phony_ >;
      _cli_options_map_["--dep-target"] =
      &::cli::thunk< options, NarrowStrings, &options::dep_target_,
        &options::dep_target_specified_ >;
      _cli_options_map_["--dep-suffix"] =
      &::cli::thunk< options, NarrowString, &options::dep_suffix_,
        &options::dep_suffix_specified_ >;
      _cli_options_map_["--dep-regex"] =
      &::cli::thunk< options, NarrowString, &options::dep_regex_,
        &options::dep_regex_specified_ >;
    }
  };

  static _cli_options_map_init _cli_options_map_init_;

  bool options::
  _parse (const char* o, ::cli::scanner& s)
  {
    _cli_options_map::const_iterator i (_cli_options_map_.find (o));

    if (i != _cli_options_map_.end ())
    {
      (*(i->second)) (*this, s);
      return true;
    }

    // options base
    //
    if (::options::_parse (o, s))
      return true;

    return false;
  }
}

// Begin epilogue.
//
//
// End epilogue.


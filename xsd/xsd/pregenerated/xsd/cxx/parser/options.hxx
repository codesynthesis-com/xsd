// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

#ifndef XSD_CXX_PARSER_OPTIONS_HXX
#define XSD_CXX_PARSER_OPTIONS_HXX

// Begin prologue.
//
//
// End prologue.

#include <cstddef>

#include <xsd/types.hxx>

#include <xsd/cxx/options.hxx>

namespace CXX
{
  namespace Parser
  {
    class options: public ::CXX::options
    {
      public:
      options ();

      options (int& argc,
               char** argv,
               bool erase = false,
               ::cli::unknown_mode option = ::cli::unknown_mode::fail,
               ::cli::unknown_mode argument = ::cli::unknown_mode::stop);

      options (int start,
               int& argc,
               char** argv,
               bool erase = false,
               ::cli::unknown_mode option = ::cli::unknown_mode::fail,
               ::cli::unknown_mode argument = ::cli::unknown_mode::stop);

      options (int& argc,
               char** argv,
               int& end,
               bool erase = false,
               ::cli::unknown_mode option = ::cli::unknown_mode::fail,
               ::cli::unknown_mode argument = ::cli::unknown_mode::stop);

      options (int start,
               int& argc,
               char** argv,
               int& end,
               bool erase = false,
               ::cli::unknown_mode option = ::cli::unknown_mode::fail,
               ::cli::unknown_mode argument = ::cli::unknown_mode::stop);

      options (::cli::scanner&,
               ::cli::unknown_mode option = ::cli::unknown_mode::fail,
               ::cli::unknown_mode argument = ::cli::unknown_mode::stop);

      // Option accessors.
      //
      const NarrowStrings&
      type_map () const;

      bool
      type_map_specified () const;

      const NarrowString&
      xml_parser () const;

      bool
      xml_parser_specified () const;

      const bool&
      generate_validation () const;

      const bool&
      suppress_validation () const;

      const bool&
      generate_polymorphic () const;

      const bool&
      generate_noop_impl () const;

      const bool&
      generate_print_impl () const;

      const bool&
      generate_test_driver () const;

      const bool&
      force_overwrite () const;

      const bool&
      root_element_first () const;

      const bool&
      root_element_last () const;

      const NarrowString&
      root_element () const;

      bool
      root_element_specified () const;

      const NarrowString&
      skel_type_suffix () const;

      bool
      skel_type_suffix_specified () const;

      const NarrowString&
      skel_file_suffix () const;

      bool
      skel_file_suffix_specified () const;

      const NarrowString&
      impl_type_suffix () const;

      bool
      impl_type_suffix_specified () const;

      const NarrowString&
      impl_file_suffix () const;

      bool
      impl_file_suffix_specified () const;

      // Print usage information.
      //
      static ::cli::usage_para
      print_usage (::std::wostream&,
                   ::cli::usage_para = ::cli::usage_para::none);

      // Implementation details.
      //
      protected:
      bool
      _parse (const char*, ::cli::scanner&);

      private:
      bool
      _parse (::cli::scanner&,
              ::cli::unknown_mode option,
              ::cli::unknown_mode argument);

      public:
      NarrowStrings type_map_;
      bool type_map_specified_;
      NarrowString xml_parser_;
      bool xml_parser_specified_;
      bool generate_validation_;
      bool suppress_validation_;
      bool generate_polymorphic_;
      bool generate_noop_impl_;
      bool generate_print_impl_;
      bool generate_test_driver_;
      bool force_overwrite_;
      bool root_element_first_;
      bool root_element_last_;
      NarrowString root_element_;
      bool root_element_specified_;
      NarrowString skel_type_suffix_;
      bool skel_type_suffix_specified_;
      NarrowString skel_file_suffix_;
      bool skel_file_suffix_specified_;
      NarrowString impl_type_suffix_;
      bool impl_type_suffix_specified_;
      NarrowString impl_file_suffix_;
      bool impl_file_suffix_specified_;
    };
  }
}

#include <xsd/cxx/parser/options.ixx>

// Begin epilogue.
//
//
// End epilogue.

#endif // XSD_CXX_PARSER_OPTIONS_HXX

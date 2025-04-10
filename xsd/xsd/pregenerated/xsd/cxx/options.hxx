// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

#ifndef XSD_CXX_OPTIONS_HXX
#define XSD_CXX_OPTIONS_HXX

// Begin prologue.
//
//
// End prologue.

#include <cstddef>

#include <xsd/types.hxx>

#include <xsd/cxx/option-types.hxx>

#include <xsd/options.hxx>

namespace CXX
{
  class options: public ::options
  {
    public:
    // Option accessors.
    //
    const cxx_version&
    std () const;

    bool
    std_specified () const;

    const NarrowString&
    char_type () const;

    bool
    char_type_specified () const;

    const NarrowString&
    char_encoding () const;

    bool
    char_encoding_specified () const;

    const NarrowString&
    output_dir () const;

    bool
    output_dir_specified () const;

    const bool&
    generate_inline () const;

    const bool&
    generate_xml_schema () const;

    const NarrowString&
    extern_xml_schema () const;

    bool
    extern_xml_schema_specified () const;

    const NarrowStrings&
    namespace_map () const;

    bool
    namespace_map_specified () const;

    const NarrowStrings&
    namespace_regex () const;

    bool
    namespace_regex_specified () const;

    const bool&
    namespace_regex_trace () const;

    const NarrowStrings&
    reserved_name () const;

    bool
    reserved_name_specified () const;

    const bool&
    include_with_brackets () const;

    const NarrowString&
    include_prefix () const;

    bool
    include_prefix_specified () const;

    const NarrowStrings&
    include_regex () const;

    bool
    include_regex_specified () const;

    const bool&
    include_regex_trace () const;

    const NarrowString&
    guard_prefix () const;

    bool
    guard_prefix_specified () const;

    const NarrowString&
    hxx_suffix () const;

    bool
    hxx_suffix_specified () const;

    const NarrowString&
    ixx_suffix () const;

    bool
    ixx_suffix_specified () const;

    const NarrowString&
    cxx_suffix () const;

    bool
    cxx_suffix_specified () const;

    const NarrowString&
    fwd_suffix () const;

    bool
    fwd_suffix_specified () const;

    const NarrowString&
    hxx_regex () const;

    bool
    hxx_regex_specified () const;

    const NarrowString&
    ixx_regex () const;

    bool
    ixx_regex_specified () const;

    const NarrowString&
    cxx_regex () const;

    bool
    cxx_regex_specified () const;

    const NarrowString&
    fwd_regex () const;

    bool
    fwd_regex_specified () const;

    const NarrowStrings&
    hxx_prologue () const;

    bool
    hxx_prologue_specified () const;

    const NarrowStrings&
    ixx_prologue () const;

    bool
    ixx_prologue_specified () const;

    const NarrowStrings&
    cxx_prologue () const;

    bool
    cxx_prologue_specified () const;

    const NarrowStrings&
    fwd_prologue () const;

    bool
    fwd_prologue_specified () const;

    const NarrowStrings&
    prologue () const;

    bool
    prologue_specified () const;

    const NarrowStrings&
    hxx_epilogue () const;

    bool
    hxx_epilogue_specified () const;

    const NarrowStrings&
    ixx_epilogue () const;

    bool
    ixx_epilogue_specified () const;

    const NarrowStrings&
    cxx_epilogue () const;

    bool
    cxx_epilogue_specified () const;

    const NarrowStrings&
    fwd_epilogue () const;

    bool
    fwd_epilogue_specified () const;

    const NarrowStrings&
    epilogue () const;

    bool
    epilogue_specified () const;

    const NarrowString&
    hxx_prologue_file () const;

    bool
    hxx_prologue_file_specified () const;

    const NarrowString&
    ixx_prologue_file () const;

    bool
    ixx_prologue_file_specified () const;

    const NarrowString&
    cxx_prologue_file () const;

    bool
    cxx_prologue_file_specified () const;

    const NarrowString&
    fwd_prologue_file () const;

    bool
    fwd_prologue_file_specified () const;

    const NarrowString&
    prologue_file () const;

    bool
    prologue_file_specified () const;

    const NarrowString&
    hxx_epilogue_file () const;

    bool
    hxx_epilogue_file_specified () const;

    const NarrowString&
    ixx_epilogue_file () const;

    bool
    ixx_epilogue_file_specified () const;

    const NarrowString&
    cxx_epilogue_file () const;

    bool
    cxx_epilogue_file_specified () const;

    const NarrowString&
    fwd_epilogue_file () const;

    bool
    fwd_epilogue_file_specified () const;

    const NarrowString&
    epilogue_file () const;

    bool
    epilogue_file_specified () const;

    const NarrowString&
    export_symbol () const;

    bool
    export_symbol_specified () const;

    const bool&
    export_xml_schema () const;

    const bool&
    export_maps () const;

    const bool&
    import_maps () const;

    const bool&
    generate_dep () const;

    const bool&
    generate_dep_only () const;

    const bool&
    dep_phony () const;

    const NarrowStrings&
    dep_target () const;

    bool
    dep_target_specified () const;

    const NarrowString&
    dep_suffix () const;

    bool
    dep_suffix_specified () const;

    const NarrowString&
    dep_file () const;

    bool
    dep_file_specified () const;

    const NarrowString&
    dep_regex () const;

    bool
    dep_regex_specified () const;

    // Print usage information.
    //
    static ::cli::usage_para
    print_usage (::std::wostream&,
                 ::cli::usage_para = ::cli::usage_para::none);

    // Implementation details.
    //
    protected:
    options ();

    bool
    _parse (const char*, ::cli::scanner&);

    public:
    cxx_version std_;
    bool std_specified_;
    NarrowString char_type_;
    bool char_type_specified_;
    NarrowString char_encoding_;
    bool char_encoding_specified_;
    NarrowString output_dir_;
    bool output_dir_specified_;
    bool generate_inline_;
    bool generate_xml_schema_;
    NarrowString extern_xml_schema_;
    bool extern_xml_schema_specified_;
    NarrowStrings namespace_map_;
    bool namespace_map_specified_;
    NarrowStrings namespace_regex_;
    bool namespace_regex_specified_;
    bool namespace_regex_trace_;
    NarrowStrings reserved_name_;
    bool reserved_name_specified_;
    bool include_with_brackets_;
    NarrowString include_prefix_;
    bool include_prefix_specified_;
    NarrowStrings include_regex_;
    bool include_regex_specified_;
    bool include_regex_trace_;
    NarrowString guard_prefix_;
    bool guard_prefix_specified_;
    NarrowString hxx_suffix_;
    bool hxx_suffix_specified_;
    NarrowString ixx_suffix_;
    bool ixx_suffix_specified_;
    NarrowString cxx_suffix_;
    bool cxx_suffix_specified_;
    NarrowString fwd_suffix_;
    bool fwd_suffix_specified_;
    NarrowString hxx_regex_;
    bool hxx_regex_specified_;
    NarrowString ixx_regex_;
    bool ixx_regex_specified_;
    NarrowString cxx_regex_;
    bool cxx_regex_specified_;
    NarrowString fwd_regex_;
    bool fwd_regex_specified_;
    NarrowStrings hxx_prologue_;
    bool hxx_prologue_specified_;
    NarrowStrings ixx_prologue_;
    bool ixx_prologue_specified_;
    NarrowStrings cxx_prologue_;
    bool cxx_prologue_specified_;
    NarrowStrings fwd_prologue_;
    bool fwd_prologue_specified_;
    NarrowStrings prologue_;
    bool prologue_specified_;
    NarrowStrings hxx_epilogue_;
    bool hxx_epilogue_specified_;
    NarrowStrings ixx_epilogue_;
    bool ixx_epilogue_specified_;
    NarrowStrings cxx_epilogue_;
    bool cxx_epilogue_specified_;
    NarrowStrings fwd_epilogue_;
    bool fwd_epilogue_specified_;
    NarrowStrings epilogue_;
    bool epilogue_specified_;
    NarrowString hxx_prologue_file_;
    bool hxx_prologue_file_specified_;
    NarrowString ixx_prologue_file_;
    bool ixx_prologue_file_specified_;
    NarrowString cxx_prologue_file_;
    bool cxx_prologue_file_specified_;
    NarrowString fwd_prologue_file_;
    bool fwd_prologue_file_specified_;
    NarrowString prologue_file_;
    bool prologue_file_specified_;
    NarrowString hxx_epilogue_file_;
    bool hxx_epilogue_file_specified_;
    NarrowString ixx_epilogue_file_;
    bool ixx_epilogue_file_specified_;
    NarrowString cxx_epilogue_file_;
    bool cxx_epilogue_file_specified_;
    NarrowString fwd_epilogue_file_;
    bool fwd_epilogue_file_specified_;
    NarrowString epilogue_file_;
    bool epilogue_file_specified_;
    NarrowString export_symbol_;
    bool export_symbol_specified_;
    bool export_xml_schema_;
    bool export_maps_;
    bool import_maps_;
    bool generate_dep_;
    bool generate_dep_only_;
    bool dep_phony_;
    NarrowStrings dep_target_;
    bool dep_target_specified_;
    NarrowString dep_suffix_;
    bool dep_suffix_specified_;
    NarrowString dep_file_;
    bool dep_file_specified_;
    NarrowString dep_regex_;
    bool dep_regex_specified_;
  };
}

#include <xsd/cxx/options.ixx>

// Begin epilogue.
//
//
// End epilogue.

#endif // XSD_CXX_OPTIONS_HXX

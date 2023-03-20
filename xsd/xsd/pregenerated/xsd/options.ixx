// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

// Begin prologue.
//
//
// End prologue.

#include <cassert>

namespace cli
{
  // usage_para
  //
  inline usage_para::
  usage_para (value v)
  : v_ (v)
  {
  }

  // unknown_mode
  //
  inline unknown_mode::
  unknown_mode (value v)
  : v_ (v)
  {
  }

  // exception
  //
  inline ::std::wostream&
  operator<< (::std::wostream& os, const exception& e)
  {
    e.print (os);
    return os;
  }

  // unknown_option
  //
  inline unknown_option::
  unknown_option (const std::string& option)
  : option_ (option)
  {
  }

  inline const std::string& unknown_option::
  option () const
  {
    return option_;
  }

  // unknown_argument
  //
  inline unknown_argument::
  unknown_argument (const std::string& argument)
  : argument_ (argument)
  {
  }

  inline const std::string& unknown_argument::
  argument () const
  {
    return argument_;
  }

  // missing_value
  //
  inline missing_value::
  missing_value (const std::string& option)
  : option_ (option)
  {
  }

  inline const std::string& missing_value::
  option () const
  {
    return option_;
  }

  // invalid_value
  //
  inline invalid_value::
  invalid_value (const std::string& option,
                 const std::string& value,
                 const std::string& message)
  : option_ (option),
    value_ (value),
    message_ (message)
  {
  }

  inline const std::string& invalid_value::
  option () const
  {
    return option_;
  }

  inline const std::string& invalid_value::
  value () const
  {
    return value_;
  }

  inline const std::string& invalid_value::
  message () const
  {
    return message_;
  }

  // file_io_failure
  //
  inline file_io_failure::
  file_io_failure (const std::string& file)
  : file_ (file)
  {
  }

  inline const std::string& file_io_failure::
  file () const
  {
    return file_;
  }

  // unmatched_quote
  //
  inline unmatched_quote::
  unmatched_quote (const std::string& argument)
  : argument_ (argument)
  {
  }

  inline const std::string& unmatched_quote::
  argument () const
  {
    return argument_;
  }

  // argv_scanner
  //
  inline argv_scanner::
  argv_scanner (int& argc,
                char** argv,
                bool erase,
                std::size_t sp)
  : start_position_ (sp + 1),
    i_ (1),
    argc_ (argc),
    argv_ (argv),
    erase_ (erase)
  {
  }

  inline argv_scanner::
  argv_scanner (int start,
                int& argc,
                char** argv,
                bool erase,
                std::size_t sp)
  : start_position_ (sp + static_cast<std::size_t> (start)),
    i_ (start),
    argc_ (argc),
    argv_ (argv),
    erase_ (erase)
  {
  }

  inline int argv_scanner::
  end () const
  {
    return i_;
  }

  // argv_file_scanner
  //
  inline argv_file_scanner::
  argv_file_scanner (int& argc,
                     char** argv,
                     const std::string& option,
                     bool erase,
                     std::size_t sp)
  : argv_scanner (argc, argv, erase, sp),
    option_ (option),
    options_ (&option_info_),
    options_count_ (1),
    i_ (1),
    skip_ (false)
  {
    option_info_.option = option_.c_str ();
    option_info_.search_func = 0;
  }

  inline argv_file_scanner::
  argv_file_scanner (int start,
                     int& argc,
                     char** argv,
                     const std::string& option,
                     bool erase,
                     std::size_t sp)
  : argv_scanner (start, argc, argv, erase, sp),
    option_ (option),
    options_ (&option_info_),
    options_count_ (1),
    i_ (1),
    skip_ (false)
  {
    option_info_.option = option_.c_str ();
    option_info_.search_func = 0;
  }

  inline argv_file_scanner::
  argv_file_scanner (const std::string& file,
                     const std::string& option,
                     std::size_t sp)
  : argv_scanner (0, zero_argc_, 0, sp),
    option_ (option),
    options_ (&option_info_),
    options_count_ (1),
    i_ (1),
    skip_ (false)
  {
    option_info_.option = option_.c_str ();
    option_info_.search_func = 0;

    load (file);
  }

  inline argv_file_scanner::
  argv_file_scanner (int& argc,
                     char** argv,
                     const option_info* options,
                     std::size_t options_count,
                     bool erase,
                     std::size_t sp)
  : argv_scanner (argc, argv, erase, sp),
    options_ (options),
    options_count_ (options_count),
    i_ (1),
    skip_ (false)
  {
  }

  inline argv_file_scanner::
  argv_file_scanner (int start,
                     int& argc,
                     char** argv,
                     const option_info* options,
                     std::size_t options_count,
                     bool erase,
                     std::size_t sp)
  : argv_scanner (start, argc, argv, erase, sp),
    options_ (options),
    options_count_ (options_count),
    i_ (1),
    skip_ (false)
  {
  }

  inline argv_file_scanner::
  argv_file_scanner (const std::string& file,
                     const option_info* options,
                     std::size_t options_count,
                     std::size_t sp)
  : argv_scanner (0, zero_argc_, 0, sp),
    options_ (options),
    options_count_ (options_count),
    i_ (1),
    skip_ (false)
  {
    load (file);
  }
}

// help_options
//

inline const std::uint64_t& help_options::
build2_metadata () const
{
  return this->build2_metadata_;
}

inline bool help_options::
build2_metadata_specified () const
{
  return this->build2_metadata_specified_;
}

inline const bool& help_options::
help () const
{
  return this->help_;
}

inline const bool& help_options::
version () const
{
  return this->version_;
}

inline const bool& help_options::
proprietary_license () const
{
  return this->proprietary_license_;
}

// options
//

inline const NarrowStrings& options::
disable_warning () const
{
  return this->disable_warning_;
}

inline bool options::
disable_warning_specified () const
{
  return this->disable_warning_specified_;
}

inline const std::string& options::
options_file () const
{
  return this->options_file_;
}

inline bool options::
options_file_specified () const
{
  return this->options_file_specified_;
}

inline const bool& options::
show_sloc () const
{
  return this->show_sloc_;
}

inline const std::size_t& options::
sloc_limit () const
{
  return this->sloc_limit_;
}

inline bool options::
sloc_limit_specified () const
{
  return this->sloc_limit_specified_;
}

inline const bool& options::
proprietary_license () const
{
  return this->proprietary_license_;
}

inline const NarrowString& options::
custom_literals () const
{
  return this->custom_literals_;
}

inline bool options::
custom_literals_specified () const
{
  return this->custom_literals_specified_;
}

inline const bool& options::
preserve_anonymous () const
{
  return this->preserve_anonymous_;
}

inline const bool& options::
show_anonymous () const
{
  return this->show_anonymous_;
}

inline const NarrowStrings& options::
anonymous_regex () const
{
  return this->anonymous_regex_;
}

inline bool options::
anonymous_regex_specified () const
{
  return this->anonymous_regex_specified_;
}

inline const bool& options::
anonymous_regex_trace () const
{
  return this->anonymous_regex_trace_;
}

inline const bool& options::
morph_anonymous () const
{
  return this->morph_anonymous_;
}

inline const NarrowStrings& options::
location_map () const
{
  return this->location_map_;
}

inline bool options::
location_map_specified () const
{
  return this->location_map_specified_;
}

inline const NarrowStrings& options::
location_regex () const
{
  return this->location_regex_;
}

inline bool options::
location_regex_specified () const
{
  return this->location_regex_specified_;
}

inline const bool& options::
location_regex_trace () const
{
  return this->location_regex_trace_;
}

inline const bool& options::
file_per_type () const
{
  return this->file_per_type_;
}

inline const NarrowStrings& options::
type_file_regex () const
{
  return this->type_file_regex_;
}

inline bool options::
type_file_regex_specified () const
{
  return this->type_file_regex_specified_;
}

inline const bool& options::
type_file_regex_trace () const
{
  return this->type_file_regex_trace_;
}

inline const NarrowStrings& options::
schema_file_regex () const
{
  return this->schema_file_regex_;
}

inline bool options::
schema_file_regex_specified () const
{
  return this->schema_file_regex_specified_;
}

inline const bool& options::
schema_file_regex_trace () const
{
  return this->schema_file_regex_trace_;
}

inline const bool& options::
fat_type_file () const
{
  return this->fat_type_file_;
}

inline const NarrowString& options::
file_list () const
{
  return this->file_list_;
}

inline bool options::
file_list_specified () const
{
  return this->file_list_specified_;
}

inline const NarrowString& options::
file_list_prologue () const
{
  return this->file_list_prologue_;
}

inline bool options::
file_list_prologue_specified () const
{
  return this->file_list_prologue_specified_;
}

inline const NarrowString& options::
file_list_epilogue () const
{
  return this->file_list_epilogue_;
}

inline bool options::
file_list_epilogue_specified () const
{
  return this->file_list_epilogue_specified_;
}

inline const NarrowString& options::
file_list_delim () const
{
  return this->file_list_delim_;
}

inline bool options::
file_list_delim_specified () const
{
  return this->file_list_delim_specified_;
}

inline const bool& options::
disable_multi_import () const
{
  return this->disable_multi_import_;
}

inline const bool& options::
disable_full_check () const
{
  return this->disable_full_check_;
}

// Begin epilogue.
//
//
// End epilogue.
// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

#ifndef XSD_OPTIONS_HXX
#define XSD_OPTIONS_HXX

// Begin prologue.
//
//
// End prologue.

#include <list>
#include <deque>
#include <iosfwd>
#include <string>
#include <cstddef>
#include <exception>

#ifndef CLI_POTENTIALLY_UNUSED
#  if defined(_MSC_VER) || defined(__xlC__)
#    define CLI_POTENTIALLY_UNUSED(x) (void*)&x
#  else
#    define CLI_POTENTIALLY_UNUSED(x) (void)x
#  endif
#endif

namespace cli
{
  class usage_para
  {
    public:
    enum value
    {
      none,
      text,
      option
    };

    usage_para (value);

    operator value () const 
    {
      return v_;
    }

    private:
    value v_;
  };

  class unknown_mode
  {
    public:
    enum value
    {
      skip,
      stop,
      fail
    };

    unknown_mode (value);

    operator value () const 
    {
      return v_;
    }

    private:
    value v_;
  };

  // Exceptions.
  //

  class exception: public std::exception
  {
    public:
    virtual void
    print (::std::wostream&) const = 0;
  };

  ::std::wostream&
  operator<< (::std::wostream&, const exception&);

  class unknown_option: public exception
  {
    public:
    virtual
    ~unknown_option () noexcept;

    unknown_option (const std::string& option);

    const std::string&
    option () const;

    virtual void
    print (::std::wostream&) const;

    virtual const char*
    what () const noexcept;

    private:
    std::string option_;
  };

  class unknown_argument: public exception
  {
    public:
    virtual
    ~unknown_argument () noexcept;

    unknown_argument (const std::string& argument);

    const std::string&
    argument () const;

    virtual void
    print (::std::wostream&) const;

    virtual const char*
    what () const noexcept;

    private:
    std::string argument_;
  };

  class missing_value: public exception
  {
    public:
    virtual
    ~missing_value () noexcept;

    missing_value (const std::string& option);

    const std::string&
    option () const;

    virtual void
    print (::std::wostream&) const;

    virtual const char*
    what () const noexcept;

    private:
    std::string option_;
  };

  class invalid_value: public exception
  {
    public:
    virtual
    ~invalid_value () noexcept;

    invalid_value (const std::string& option,
                   const std::string& value,
                   const std::string& message = std::string ());

    const std::string&
    option () const;

    const std::string&
    value () const;

    const std::string&
    message () const;

    virtual void
    print (::std::wostream&) const;

    virtual const char*
    what () const noexcept;

    private:
    std::string option_;
    std::string value_;
    std::string message_;
  };

  class eos_reached: public exception
  {
    public:
    virtual void
    print (::std::wostream&) const;

    virtual const char*
    what () const noexcept;
  };

  class file_io_failure: public exception
  {
    public:
    virtual
    ~file_io_failure () noexcept;

    file_io_failure (const std::string& file);

    const std::string&
    file () const;

    virtual void
    print (::std::wostream&) const;

    virtual const char*
    what () const noexcept;

    private:
    std::string file_;
  };

  class unmatched_quote: public exception
  {
    public:
    virtual
    ~unmatched_quote () noexcept;

    unmatched_quote (const std::string& argument);

    const std::string&
    argument () const;

    virtual void
    print (::std::wostream&) const;

    virtual const char*
    what () const noexcept;

    private:
    std::string argument_;
  };

  // Command line argument scanner interface.
  //
  // The values returned by next() are guaranteed to be valid
  // for the two previous arguments up until a call to a third
  // peek() or next().
  //
  // The position() function returns a monotonically-increasing
  // number which, if stored, can later be used to determine the
  // relative position of the argument returned by the following
  // call to next(). Note that if multiple scanners are used to
  // extract arguments from multiple sources, then the end
  // position of the previous scanner should be used as the
  // start position of the next.
  //
  class scanner
  {
    public:
    virtual
    ~scanner ();

    virtual bool
    more () = 0;

    virtual const char*
    peek () = 0;

    virtual const char*
    next () = 0;

    virtual void
    skip () = 0;

    virtual std::size_t
    position () = 0;
  };

  class argv_scanner: public scanner
  {
    public:
    argv_scanner (int& argc,
                  char** argv,
                  bool erase = false,
                  std::size_t start_position = 0);

    argv_scanner (int start,
                  int& argc,
                  char** argv,
                  bool erase = false,
                  std::size_t start_position = 0);

    int
    end () const;

    virtual bool
    more ();

    virtual const char*
    peek ();

    virtual const char*
    next ();

    virtual void
    skip ();

    virtual std::size_t
    position ();

    protected:
    std::size_t start_position_;
    int i_;
    int& argc_;
    char** argv_;
    bool erase_;
  };

  class argv_file_scanner: public argv_scanner
  {
    public:
    argv_file_scanner (int& argc,
                       char** argv,
                       const std::string& option,
                       bool erase = false,
                       std::size_t start_position = 0);

    argv_file_scanner (int start,
                       int& argc,
                       char** argv,
                       const std::string& option,
                       bool erase = false,
                       std::size_t start_position = 0);

    argv_file_scanner (const std::string& file,
                       const std::string& option,
                       std::size_t start_position = 0);

    struct option_info
    {
      // If search_func is not NULL, it is called, with the arg
      // value as the second argument, to locate the options file.
      // If it returns an empty string, then the file is ignored.
      //
      const char* option;
      std::string (*search_func) (const char*, void* arg);
      void* arg;
    };

    argv_file_scanner (int& argc,
                        char** argv,
                        const option_info* options,
                        std::size_t options_count,
                        bool erase = false,
                        std::size_t start_position = 0);

    argv_file_scanner (int start,
                       int& argc,
                       char** argv,
                       const option_info* options,
                       std::size_t options_count,
                       bool erase = false,
                       std::size_t start_position = 0);

    argv_file_scanner (const std::string& file,
                       const option_info* options = 0,
                       std::size_t options_count = 0,
                       std::size_t start_position = 0);

    virtual bool
    more ();

    virtual const char*
    peek ();

    virtual const char*
    next ();

    virtual void
    skip ();

    virtual std::size_t
    position ();

    // Return the file path if the peeked at argument came from a file and
    // the empty string otherwise. The reference is guaranteed to be valid
    // till the end of the scanner lifetime.
    //
    const std::string&
    peek_file ();

    // Return the 1-based line number if the peeked at argument came from
    // a file and zero otherwise.
    //
    std::size_t
    peek_line ();

    private:
    const option_info*
    find (const char*) const;

    void
    load (const std::string& file);

    typedef argv_scanner base;

    const std::string option_;
    option_info option_info_;
    const option_info* options_;
    std::size_t options_count_;

    struct arg
    {
      std::string value;
      const std::string* file;
      std::size_t line;
    };

    std::deque<arg> args_;
    std::list<std::string> files_;

    // Circular buffer of two arguments.
    //
    std::string hold_[2];
    std::size_t i_;

    bool skip_;

    static int zero_argc_;
    static std::string empty_string_;
  };

  template <typename X>
  struct parser;
}

#include <cstddef>

#include <cstdint>

#include <xsd/types.hxx>

class help_options
{
  public:
  help_options ();

  help_options (int& argc,
                char** argv,
                bool erase = false,
                ::cli::unknown_mode option = ::cli::unknown_mode::fail,
                ::cli::unknown_mode argument = ::cli::unknown_mode::stop);

  help_options (int start,
                int& argc,
                char** argv,
                bool erase = false,
                ::cli::unknown_mode option = ::cli::unknown_mode::fail,
                ::cli::unknown_mode argument = ::cli::unknown_mode::stop);

  help_options (int& argc,
                char** argv,
                int& end,
                bool erase = false,
                ::cli::unknown_mode option = ::cli::unknown_mode::fail,
                ::cli::unknown_mode argument = ::cli::unknown_mode::stop);

  help_options (int start,
                int& argc,
                char** argv,
                int& end,
                bool erase = false,
                ::cli::unknown_mode option = ::cli::unknown_mode::fail,
                ::cli::unknown_mode argument = ::cli::unknown_mode::stop);

  help_options (::cli::scanner&,
                ::cli::unknown_mode option = ::cli::unknown_mode::fail,
                ::cli::unknown_mode argument = ::cli::unknown_mode::stop);

  // Option accessors.
  //
  const std::uint64_t&
  build2_metadata () const;

  bool
  build2_metadata_specified () const;

  const bool&
  help () const;

  const bool&
  version () const;

  const bool&
  proprietary_license () const;

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
  std::uint64_t build2_metadata_;
  bool build2_metadata_specified_;
  bool help_;
  bool version_;
  bool proprietary_license_;
};

class options
{
  public:
  // Option accessors.
  //
  const NarrowStrings&
  disable_warning () const;

  bool
  disable_warning_specified () const;

  const std::string&
  options_file () const;

  bool
  options_file_specified () const;

  const bool&
  show_sloc () const;

  const std::size_t&
  sloc_limit () const;

  bool
  sloc_limit_specified () const;

  const bool&
  proprietary_license () const;

  const NarrowString&
  custom_literals () const;

  bool
  custom_literals_specified () const;

  const bool&
  preserve_anonymous () const;

  const bool&
  show_anonymous () const;

  const NarrowStrings&
  anonymous_regex () const;

  bool
  anonymous_regex_specified () const;

  const bool&
  anonymous_regex_trace () const;

  const bool&
  morph_anonymous () const;

  const NarrowStrings&
  location_map () const;

  bool
  location_map_specified () const;

  const NarrowStrings&
  location_regex () const;

  bool
  location_regex_specified () const;

  const bool&
  location_regex_trace () const;

  const bool&
  file_per_type () const;

  const NarrowStrings&
  type_file_regex () const;

  bool
  type_file_regex_specified () const;

  const bool&
  type_file_regex_trace () const;

  const NarrowStrings&
  schema_file_regex () const;

  bool
  schema_file_regex_specified () const;

  const bool&
  schema_file_regex_trace () const;

  const bool&
  fat_type_file () const;

  const NarrowString&
  file_list () const;

  bool
  file_list_specified () const;

  const bool&
  file_list_only () const;

  const NarrowString&
  file_list_prologue () const;

  bool
  file_list_prologue_specified () const;

  const NarrowString&
  file_list_epilogue () const;

  bool
  file_list_epilogue_specified () const;

  const NarrowString&
  file_list_delim () const;

  bool
  file_list_delim_specified () const;

  const bool&
  disable_multi_import () const;

  const bool&
  disable_full_check () const;

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
  NarrowStrings disable_warning_;
  bool disable_warning_specified_;
  std::string options_file_;
  bool options_file_specified_;
  bool show_sloc_;
  std::size_t sloc_limit_;
  bool sloc_limit_specified_;
  bool proprietary_license_;
  NarrowString custom_literals_;
  bool custom_literals_specified_;
  bool preserve_anonymous_;
  bool show_anonymous_;
  NarrowStrings anonymous_regex_;
  bool anonymous_regex_specified_;
  bool anonymous_regex_trace_;
  bool morph_anonymous_;
  NarrowStrings location_map_;
  bool location_map_specified_;
  NarrowStrings location_regex_;
  bool location_regex_specified_;
  bool location_regex_trace_;
  bool file_per_type_;
  NarrowStrings type_file_regex_;
  bool type_file_regex_specified_;
  bool type_file_regex_trace_;
  NarrowStrings schema_file_regex_;
  bool schema_file_regex_specified_;
  bool schema_file_regex_trace_;
  bool fat_type_file_;
  NarrowString file_list_;
  bool file_list_specified_;
  bool file_list_only_;
  NarrowString file_list_prologue_;
  bool file_list_prologue_specified_;
  NarrowString file_list_epilogue_;
  bool file_list_epilogue_specified_;
  NarrowString file_list_delim_;
  bool file_list_delim_specified_;
  bool disable_multi_import_;
  bool disable_full_check_;
};

#include <xsd/options.ixx>

// Begin epilogue.
//
//
// End epilogue.

#endif // XSD_OPTIONS_HXX

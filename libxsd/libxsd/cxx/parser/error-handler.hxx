// file      : libxsd/cxx/parser/error-handler.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef LIBXSD_CXX_PARSER_ERROR_HANDLER_HXX
#define LIBXSD_CXX_PARSER_ERROR_HANDLER_HXX

#include <libxsd/cxx/xml/error-handler.hxx>

#include <libxsd/cxx/parser/exceptions.hxx>

namespace xsd
{
  namespace cxx
  {
    namespace parser
    {
      template <typename C>
      class error_handler: public xml::error_handler<C>
      {
      public:
        typedef typename xml::error_handler<C>::severity severity;

        error_handler ()
            : failed_ (false)
        {
        }

        virtual bool
        handle (const std::basic_string<C>& id,
                unsigned long line,
                unsigned long column,
                severity s,
                const std::basic_string<C>& message);

        void
        throw_if_failed () const;

        void
        reset ()
        {
          failed_ = false;
          diagnostics_.clear ();
        }

      private:
        bool failed_;
        diagnostics<C> diagnostics_;
      };
    }
  }
}

#include <libxsd/cxx/parser/error-handler.txx>

#endif  // LIBXSD_CXX_PARSER_ERROR_HANDLER_HXX

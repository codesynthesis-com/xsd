// file      : cxx/tree/secure/secure-dom-parser.hxx
// copyright : not copyrighted - public domain

#ifndef SECURE_DOM_PARSER_HXX
#define SECURE_DOM_PARSER_HXX

#include <xercesc/parsers/DOMLSParserImpl.hpp>

class SecureDOMParser: public xercesc::DOMLSParserImpl
{
public:
  SecureDOMParser (xercesc::MemoryManager* mm =
                     xercesc::XMLPlatformUtils::fgMemoryManager,
                   xercesc::XMLGrammarPool* gp = 0)
      : DOMLSParserImpl (0, mm, gp) {}

  virtual void
  doctypeDecl (const xercesc::DTDElementDecl& root,
               const XMLCh* const             public_id,
               const XMLCh* const             system_id,
               const bool                     has_internal,
               const bool                     has_external);
};

#endif // SECURE_DOM_PARSER_HXX

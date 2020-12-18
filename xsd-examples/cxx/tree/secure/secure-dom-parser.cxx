// file      : cxx/tree/secure/secure-dom-parser.cxx
// copyright : not copyrighted - public domain

#include "secure-dom-parser.hxx"

#include <xercesc/util/XMLException.hpp>
#include <xercesc/util/XMLExceptMsgs.hpp>

using namespace xercesc;

void SecureDOMParser::
doctypeDecl (const DTDElementDecl& e,
             const XMLCh* const    pub_id,
             const XMLCh* const    sys_id,
             const bool            hasi,
             const bool            hase)
{
  if (hasi || hase)
    ThrowXMLwithMemMgr(RuntimeException,
                       XMLExcepts::Gen_NoDTDValidator,
                       fMemoryManager);

  DOMLSParserImpl::doctypeDecl (e, pub_id, sys_id, hasi, hase);
}

// file      : xsd/xsd.hxx
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_XSD_HXX
#define XSD_XSD_HXX

#include <set>
#include <vector>
#include <cstdio> // std::remove

#include <libcutl/shared-ptr.hxx>
#include <libcutl/fs/auto-remove.hxx>

#include <libxsd-frontend/semantic-graph/elements.hxx> // Path

#include <xsd/types.hxx>

typedef std::set<NarrowString> WarningSet;
typedef std::vector<NarrowString> FileList;

typedef cutl::fs::auto_remove AutoUnlink;
typedef cutl::fs::auto_removes AutoUnlinks;

#endif // XSD_XSD_HXX

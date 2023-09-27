# XSD

XSD is an open-source, cross-platform XML Schema to C++ data binding
compiler. Provided with an XML document specification (XML Schema), it
generates C++ classes that represent the given vocabulary as well as XML
parsing and serialization code. You can then access the data stored in XML
using types and functions that semantically correspond to your application
domain rather than dealing with generic elements/attributes and raw strings.

For further information, refer to the [XSD project
page](https://codesynthesis.com/products/xsd/).

## Usage

XSD consists of several packages with the main ones being `xsd` (the XML
Schema to C++ compiler) and `libxsd` (the runtime library). There are also
several `*-tests` packages as well as `xsd-examples`.

When specifying dependencies on XSD packages in your project, the `xsd`
package should be a build-time dependency. The `libxsd` library is
header-only and because it can be used either with Xerces-C++ or
Expat as the underlying XML parser, it does not have a dependency on
either, expecting your project to make the choice by depending on
one or the other explicitly and then importing and linking the
corresponding library.

So, putting it all together, your project's `manifest` would normally
have the following fragment if using Xerces-C++:

```
depends: * xsd ^4.2.0
depends: libxsd ^4.2.0
depends  libxerces-c ^3.2.4
```

Or the following fragment if using Expat:

```
depends: * xsd ^4.2.0
depends: libxsd ^4.2.0
depends  libexpat ^2.5.0
```

Then your `buildfile` would have something along these lines if using
Xerces-C++:

```
import! [metadata] xsd = xsd%exe{xsd}

import libs  = libxsd%lib{xsd}
import libs += libxerces-c%lib{xerces-c}
```

Or along these lines if using Expat:

```
import! [metadata] xsd = xsd%exe{xsd}

import libs  = libxsd%lib{xsd}
import libs += libexpat%lib{expat}
```

Note that the `xsd` executable provides `build2` metadata.

The compilation of XML Schema to C++ can be implemented using ad hoc recipes
or rules. See the `xsd-examples` package for the complete examples.

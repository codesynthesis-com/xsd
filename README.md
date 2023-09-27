# XSD

XSD is an open-source, cross-platform XML Schema to C++ data binding
compiler. Provided with an XML document specification (XML Schema), it
generates C++ classes that represent the given vocabulary as well as XML
parsing and serialization code. You can then access the data stored in XML
using types and functions that semantically correspond to your application
domain rather than dealing with generic elements/attributes and raw strings.

For further information, including licensing conditions, documentation, and
binary packages, refer to the [XSD project
page](https://codesynthesis.com/products/xsd/).

NOTE: the steps described below are more appropriate for the development of
XSD as opposed to consumption. In case you just want to use XSD:

* If you want to use a binary package, see the [XSD download
  page](https://codesynthesis.com/products/xsd/download.xhtml).

* If you want to build XSD from source and use the result from a project that
  uses a build system other than `build2`, then see [Installing XSD with
  `build2`](https://codesynthesis.com/products/xsd/doc/install-build2.xhtml)
  for the step-by-step instructions.

* If you want to use XSD from a project that uses `build2` as the build
  system, then see the accompanying `PACKAGE-README.md` file.

The development setup for XSD uses two build configurations, for example:

```
git clone .../xsd.git
cd xsd

bdep init --empty

bdep config create @host ../xsd-host --type host cc config.cxx=g++
bdep config create @target ../xsd-target cc config.cxx=g++

bdep init @host -d xsd
bdep init @target -d libxsd -d libxsd-tests -d xsd-tests -d xsd-examples

```

To generate the documentation in the `.ps` and `.pdf` formats, the `html2ps`
and `ps2pdf14` programs are required (the latter is from `ghostscript`). A
warning is issued in the development mode if these programs are not available.

To generate the Doxygen documentation (in `libxsd`) the `doxygen` program is
required. Currently this functionality is only enabled if `libxsd` is
initialized with explicit `config.libxsd.doxygen=true`.

To test installation of the XSD compiler, create a separate target
configuration (it will automatically resolve any build-time dependencies from
`host`):

```
bdep config create @install ../xsd-install --type target cc config.cxx=g++ \
  config.install.root=/tmp/install

bdep init @install -d xsd

b install: ../xsd-install/xsd/
```

The checked out `libxsd/xsd/cxx/version.hxx` will be overwritten during the
in-source build but these changes must be ignored. To do this automatically,
run:

```
git update-index --assume-unchanged libxsd/xsd/cxx/version.hxx
```

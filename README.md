# XSD

XSD is an XML Schema to C++ compiler.

NOTE: the steps described below are more appropriate for the development of
XSD as opposed to consumption. If you just want to use XSD, see [Installing
XSD with `build2`](https://codesynthesis.com/products/xsd/doc/install-build2.xhtml)
for the step by step instructions.

The development setup for XSD uses two configurations, for example:

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

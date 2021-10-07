# XSD

XSD is an XML Schema to C++ compiler.

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

To generate the documentation in the `.ps` and `.pdf` formats, `html2ps` and
`ps2pdf14` programs are required (the latter is from `ghostscript`). A warning
is issued in the development mode if these programs are not available.

To test installation of the XSD compiler, create a separate target
configuration (it will automatically resolve any build-time dependencies from
`host`):

```
bdep config create @install ../xsd-install --type target cc config.cxx=g++ \
  config.install.root=/tmp/install

bdep init @install -d xsd

b install: ../xsd-install/xsd/
```

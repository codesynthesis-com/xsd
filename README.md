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

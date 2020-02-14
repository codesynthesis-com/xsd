#! /usr/bin/env bash

version=4.1.0.a11

trap 'exit 1' ERR
set -o errtrace # Trap in functions.

function info () { echo "$*" 1>&2; }
function error () { info "$*"; exit 1; }

date="$(date +"%B %Y")"
copyright="$(sed -n -re 's%^Copyright \(c\) (.+)\.$%\1%p' ../LICENSE)"

while [ $# -gt 0 ]; do
  case $1 in
    --clean)
      rm -f xsd.xhtml xsd.1
      rm -f cxx/parser/guide/cxx-parser-guide.{ps,pdf}
      rm -f cxx/tree/guide/cxx-tree-guide.{ps,pdf}
      rm -f cxx/tree/manual/cxx-tree-manual.{ps,pdf}
      exit 0
      ;;
    *)
      error "unexpected $1"
      ;;
  esac
done

ops=(\
-v project="xsd" \
-v version="$version" \
-v date="$date" \
-v copyright="$copyright" \
-I ../xsd \
--stdout \
--suppress-undocumented \
--exclude-base)

# XHTML
#
# Common options.
#
cli "${ops[@]}" --generate-html --class CXX::options --class options \
--html-prologue-file xsd-prologue.xhtml \
../xsd/cxx/options.cli >xsd.xhtml

# C++/Tree options.
#
cli "${ops[@]}" --generate-html \
--html-prologue-file xsd-tree-header.xhtml \
../xsd/cxx/tree/options.cli >>xsd.xhtml

# C++/Parser options.
#
cli "${ops[@]}" --generate-html \
--html-prologue-file xsd-parser-header.xhtml \
--html-epilogue-file xsd-epilogue.xhtml \
../xsd/cxx/parser/options.cli >>xsd.xhtml

# MAN
#
# Common options.
#
cli "${ops[@]}" --generate-man --class CXX::options --class options \
--man-prologue-file xsd-prologue.1 \
../xsd/cxx/options.cli >xsd.1

# C++/Tree options.
#
cli "${ops[@]}" --generate-man \
--man-prologue-file xsd-tree-header.1 \
../xsd/cxx/tree/options.cli >>xsd.1

# C++/Parser options.
#
cli "${ops[@]}" --generate-man \
--man-prologue-file xsd-parser-header.1 \
--man-epilogue-file xsd-epilogue.1  \
../xsd/cxx/parser/options.cli >>xsd.1

# PS, PDF
#
# C++/Parser guide.
#
html2ps -f cxx/parser/guide/guide.html2ps \
-o cxx/parser/guide/cxx-parser-guide.ps cxx/parser/guide/index.xhtml

ps2pdf14 -dOptimize=true -dEmbedAllFonts=true \
cxx/parser/guide/cxx-parser-guide.ps cxx/parser/guide/cxx-parser-guide.pdf

# C++/Tree guide.
#
html2ps -f cxx/tree/guide/guide.html2ps \
-o cxx/tree/guide/cxx-tree-guide.ps cxx/tree/guide/index.xhtml

ps2pdf14 -dOptimize=true -dEmbedAllFonts=true \
cxx/tree/guide/cxx-tree-guide.ps cxx/tree/guide/cxx-tree-guide.pdf

# C++/Tree manual.
#
html2ps -f cxx/tree/manual/manual.html2ps \
-o cxx/tree/manual/cxx-tree-manual.ps cxx/tree/manual/index.xhtml

ps2pdf14 -dOptimize=true -dEmbedAllFonts=true \
cxx/tree/manual/cxx-tree-manual.ps cxx/tree/manual/cxx-tree-manual.pdf

# file      : buildfile
# license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

# Glue buildfile that "pulls" all the packages.

import pkgs = */
./: $pkgs

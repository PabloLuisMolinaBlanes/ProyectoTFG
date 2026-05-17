#!/bin/bash
VERSION=v5.5.3
IDF_TOOLS_PATH=$HOME/.espressif/$VERSION/esp-idf/tools
bash -c "source '$HOME/.espressif/tools/activate_idf_$VERSION.sh';$IDF_TOOLS_PATH/idf.py -p /dev/ttyUSB0 build"

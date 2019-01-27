#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/hopecoin.ico

convert ../../src/qt/res/icons/hopecoin-16.png ../../src/qt/res/icons/hopecoin-32.png ../../src/qt/res/icons/hopecoin-48.png ${ICON_DST}

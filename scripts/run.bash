#!/bin/bash

BASEDIR=$(dirname $(realpath $0))
cd $BASEDIR/..

if [[ "$1" == "big" ]]; then
    build/compress -o examples/bigdata.pkg examples/bigdata.bin
    # build/compress -x -o examples/bigdata2.bin examples/bigdata.pkg
else 
    build/compress examples/text.txt -o examples/text.bin
    build/compress -x -o examples/utext.txt examples/text.bin
fi
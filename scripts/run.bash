#!/bin/bash

BASEDIR=$(dirname $(realpath $0))
cd $BASEDIR/..

build/compress examples/text.txt -o examples/text.bin
build/compress -x -o examples/utext.txt examples/text.bin
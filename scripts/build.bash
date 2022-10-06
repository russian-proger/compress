#!/usr/bin/bash

BASEDIR=$(dirname $(realpath $0))

mkdir -p build
cd $BASEDIR/../build
cmake ../
make
#!/bin/bash

BASEDIR=$(dirname $(realpath $0))
cd $BASEDIR/..

./build/compress examples/main.cpp -o examples/main.txt
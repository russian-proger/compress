#!/bin/bash

BASEDIR=$(dirname $(realpath $0))
cd $BASEDIR/..

./build/compress assets/main.cpp -o assets/main.txt
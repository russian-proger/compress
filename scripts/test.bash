#!/bin/bash

BASEDIR=$(dirname $(realpath $0))
cd $BASEDIR/..

g++ test.cpp -o test && ./test
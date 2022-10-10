#!/bin/bash

BASEDIR=$(dirname $(realpath $0))
cd $BASEDIR/..

./build/compress assets/data.txt -o assets/data.cmp
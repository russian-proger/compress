#!/usr/bin/bash

BASEDIR=$(dirname $(realpath $0))

cd $BASEDIR/../

mkdir -p build
cd build

if [[ "$1" == "debug" ]]; then
    cmake -DCMAKE_BUILD_TYPE=Debug ../
elif [[ "$1" == "release" ]]; then
    cmake -DCMAKE_BUILD_TYPE=Release ../
else
    cmake ../
fi

cmake --build .
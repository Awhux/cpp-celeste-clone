#!/bin/bash
EXENAME="celeste.exe"

if [ -d "build" ]; then
    rm -rf build
fi

mkdir build

clang++ -g $(find src -name "*.cpp") -o build/$EXENAME
#!/bin/bash
EXENAME="celeste.exe"

LIBS="-luser32 -lopengl32"
WARNINGS="-Wno-writable-strings -Wmacro-redefined"
EXTENSIONS="-std=c++17"

if [ -d "build" ]; then
    rm -rf build
fi

mkdir build

clang++ -g $(find src -name "*.cpp") -o build/$EXENAME -Isrc/include -Lsrc/lib $LIBS $WARNINGS $EXTENSIONS
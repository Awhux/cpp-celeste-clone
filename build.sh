#!/bin/bash
EXENAME="celeste.exe"

LIBS="-luser32 -lopengl32 -lgdi32 -Lsrc/lib"
WARNINGS="-Wno-writable-strings -Wmacro-redefined -Wdeprecated-declarations"
EXTENSIONS="-std=c++17"

if [ -d "build" ]; then
    rm -rf build
fi

mkdir build

clang++ -D_CRT_SECURE_NO_WARNINGS -Isrc/include $LIBS $WARNINGS $EXTENSIONS -g $(find src -name "*.cpp") -o build/$EXENAME
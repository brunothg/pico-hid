#!/bin/bash

GENERATOR="Unix Makefiles"
GENERATOR_EXEC="make"
if command -v ninja &> /dev/null ;then
	GENERATOR="Ninja"
	GENERATOR_EXEC="ninja"
fi

mkdir -p build/release
cd build/release
cmake -G "$GENERATOR" -DCMAKE_BUILD_TYPE=Release ../..
cmake --build .
cd ../..

mkdir -p bin
cp build/release/pico-hid.* bin


#!/bin/bash

if [[ "$OSTYPE" == "msys" ]]; then
	gen="MSYS Makefiles"
else
	gen="Unix Makefiles"
fi

mkdir -p build && cd build
cmake .. -G"$gen" -DCMAKE_BUILD_TYPE="Release"
cmake --build .

cd .. && cd bin
./sdl2-shooter-test
./sdl2-shooter

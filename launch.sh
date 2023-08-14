#!/bin/bash

mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE="Debug" ..
make

cd .. && cd bin
./sdl2-shooter-test
./sdl2-shooter

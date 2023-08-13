#!/bin/bash

mkdir -p build && cd build
cmake ..
make

cd .. && cd bin
./sdl2-shooter-test
./sdl2-shooter

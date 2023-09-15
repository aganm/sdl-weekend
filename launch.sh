#!/bin/bash

game=$1

if [[ "$OSTYPE" == "msys" ]]; then
	gen="MSYS Makefiles"
else
	gen="Unix Makefiles"
fi

mkdir -p bin && rm bin/*
mkdir -p build && cd build
cmake .. -G"$gen" -DCMAKE_BUILD_TYPE="Release" -DGAME="$game"
cmake --build .

cd .. && cd bin
./"$game"_test
./"$game"

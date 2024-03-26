#!/bin/bash
# export CC=tcc
# export CXX=clang++

game=$(basename $1)

if [[ "$OSTYPE" == "msys" ]]; then
	gen="MSYS Makefiles"
else
	gen="Unix Makefiles"
fi

if [ -f $game/standalone ]; then
	standalone="Yes"
fi

mkdir -p build && cd build

cmake .. -G"$gen" \
	-DCMAKE_BUILD_TYPE="Release" \
	-DOUTPUT="bin" \
	-DGAME="$game" \
	-DSTANDALONE="$standalone"

cmake --build .

cd .. && cd bin
./"$game"_test
./"$game"

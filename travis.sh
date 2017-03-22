#!/usr/bin/env sh
set -evx
env | sort

mkdir build || true
mkdir build/$LIBBR_TARGET || true
cd build/$LIBBR_TARGET
cmake -DLIBBR_ENABLE_CXX14=$LIBBR_ENABLE_CXX14 \
      -DLIBBR_BUILD_32_BITS=$LIBBR_BUILD_32_BITS \
      ../../
cmake --build . --target br_test -- -j 8
./test/br_test.exe
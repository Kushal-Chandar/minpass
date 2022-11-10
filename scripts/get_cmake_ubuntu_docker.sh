#!/bin/bash

# Please remove the existing cmake package before running this script

cmake_version="$1"
jobs="$2"
if [ -z "$cmake_version" ]
then
      cmake_version=$(curl -s 'https://cmake.org/files/LatestRelease/cmake-latest-files-v1.json' | jq -r '.version.string')
fi
if [ -z "$jobs" ]
then
      jobs=$(nproc)
fi


curl -OL https://github.com/Kitware/CMake/releases/download/v$cmake_version/cmake-$cmake_version.tar.gz
tar -xzf cmake-$cmake_version.tar.gz
cd cmake-$cmake_version
./bootstrap -- -DCMAKE_BUILD_TYPE:STRING=Release
make -j$jobs && make install

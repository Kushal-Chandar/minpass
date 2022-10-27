#!/bin/bash

cmake_version="$1"
jobs="$2"
if [ -z "$cmake_version" ]
then
      cmake_version=$(curl -s 'https://cmake.org/files/LatestRelease/cmake-latest-files-v1.json' | jq -r '.version.string')
fi
if [ -z "$jobs" ]
then
      jobs=$(cat /proc/cpuinfo | grep processor | wc -l)
fi


curl -OL https://github.com/Kitware/CMake/releases/download/v$cmake_version/cmake-$cmake_version.tar.gz
tar -xzvf cmake-$cmake_version.tar.gz > dev/null
cd cmake-$cmake_version
./bootstrap -- -DCMAKE_BUILD_TYPE:STRING=Release
make -j$jobs && make install

cmake_minimum_required(VERSION 3.24)

project(minpass LANGUAGES CXX)

include(cmake/init.cmake)

###########################################
### Global target is this executable
###########################################
add_executable(minpass)

###########################################
### adding sources
###########################################
add_subdirectory(src)

cmake_minimum_required(VERSION 3.24)

project(minpass LANGUAGES CXX)

include(cmake/init.cmake)

add_library(minpasslib STATIC)
target_sources(minpasslib PRIVATE src/minpass/minpass.cc
                                  include/minpass/minpass.h)
target_link_libraries(minpasslib PRIVATE project_compile_options)
target_include_directories(minpasslib PUBLIC include)

find_package(SQLite3 REQUIRED)
target_link_libraries(minpasslib PRIVATE SQLite::SQLite3)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(minpasslib PRIVATE fmt::fmt)
# a target linking to this library doesnot need to have its includes in its target include libraries

add_executable(minpass)
target_sources(minpass PRIVATE src/main.cc)
target_link_libraries(minpass PRIVATE project_compile_options)
# target_link_libraries(minpass PRIVATE minpasslib)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(minpass PRIVATE fmt::fmt)

# link winsock
if(WIN32)
  target_link_libraries(minpass PRIVATE wsock32 ws2_32)
endif()

find_package(OpenSSL REQUIRED)
target_link_libraries(minpass PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_compile_definitions(minpass PUBLIC CPPHTTPLIB_OPENSSL_SUPPORT)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(minpass PRIVATE nlohmann_json::nlohmann_json)
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)

cmake_minimum_required(VERSION 3.24)

project(minpass LANGUAGES CXX)

include(cmake/init.cmake)

# add_library(database_lib STATIC)
# target_sources(database_lib PRIVATE src/database_lib.cc include/database_lib.h)
# target_link_libraries(database_lib PRIVATE project_compile_options)
# target_include_directories(database_lib PUBLIC include)

# find_package(SQLite3 REQUIRED)
# target_link_libraries(database_lib PRIVATE SQLite::SQLite3)

# find_package(fmt CONFIG REQUIRED)
# target_link_libraries(database_lib PRIVATE fmt::fmt)
# a target linking to this library doesnot need to have its includes in its target include libraries

add_executable(minpass)
target_sources(minpass PRIVATE src/main.cc)
target_link_libraries(minpass PRIVATE project_compile_options)
# target_link_libraries(minpass PRIVATE database_lib)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(minpass PRIVATE fmt::fmt)

find_package(Drogon CONFIG REQUIRED)
target_link_libraries(minpass PRIVATE Drogon::Drogon)

# For drogon compilation to work
# link winsock, winsock2, iphlpapi (Googled for undefined references and link those libraries where they are found)
if(WIN32)
  target_link_libraries(minpass PRIVATE wsock32 ws2_32 iphlpapi)
endif()

find_package(OpenSSL REQUIRED)
target_link_libraries(minpass PRIVATE OpenSSL::SSL OpenSSL::Crypto)

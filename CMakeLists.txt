cmake_minimum_required(VERSION 3.24)

project(minpass LANGUAGES CXX)

include(cmake/init.cmake)

find_package(Drogon CONFIG REQUIRED)

add_library(sqlite3_queries STATIC)
target_sources(sqlite3_queries PRIVATE src/sqlite3_queries.cc
                                       include/sqlite3_queries.h)
target_link_libraries(sqlite3_queries PRIVATE project_compile_options)
target_include_directories(sqlite3_queries PUBLIC include)
target_link_libraries(sqlite3_queries PRIVATE Drogon::Drogon)
# a target linking to this library doesnot need to have its includes in its target include libraries

add_library(sqlite3_client STATIC)
target_sources(sqlite3_client PRIVATE src/sqlite3_client.cc
                                      include/sqlite3_client.h)
target_link_libraries(sqlite3_client PRIVATE project_compile_options)
target_include_directories(sqlite3_client PUBLIC include)
target_link_libraries(sqlite3_client PRIVATE sqlite3_queries)
target_link_libraries(sqlite3_client PRIVATE Drogon::Drogon)

add_executable(minpass)
target_sources(minpass PRIVATE src/main.cc)
target_link_libraries(minpass PRIVATE project_compile_options)
target_link_libraries(minpass PRIVATE sqlite3_client)
target_link_libraries(minpass PRIVATE Drogon::Drogon)

# For drogon compilation to work
# link winsock, winsock2, iphlpapi (Googled for undefined references and link those libraries where they are found)
if(WIN32)
  target_link_libraries(minpass PRIVATE wsock32 ws2_32 iphlpapi)
endif()

find_package(OpenSSL REQUIRED)
target_link_libraries(minpass PRIVATE OpenSSL::SSL OpenSSL::Crypto)

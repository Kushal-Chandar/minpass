cmake_minimum_required(VERSION 3.24)

project(minpass LANGUAGES CXX)

include(cmake/init.cmake)

###########################################
### Required packages
###########################################
find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

###########################################
### Utilities
###########################################
add_library(utilities STATIC)
target_sources(utilities PRIVATE src/utilities/strong_type.cc
                                 include/utilities/strong_types.h)
target_link_libraries(utilities PRIVATE project_compile_options)
target_include_directories(utilities PUBLIC include)

###########################################
### Types
###########################################
add_library(Types STATIC)
target_sources(Types PRIVATE src/types.cc include/types.h)
target_link_libraries(Types PRIVATE project_compile_options)
target_link_libraries(Types PRIVATE utilities)
target_include_directories(Types PUBLIC include)

###########################################
### SQLite3_Queries
###########################################
add_library(sqlite3_queries STATIC)
target_sources(sqlite3_queries PRIVATE src/sqlite3_queries.cc
                                       include/sqlite3_queries.h)
target_link_libraries(sqlite3_queries PRIVATE project_compile_options)
target_include_directories(sqlite3_queries PUBLIC include)
target_link_libraries(sqlite3_queries PRIVATE Drogon::Drogon)
target_link_libraries(sqlite3_queries PRIVATE utilities)

###########################################
### SQLite3_Client
###########################################
add_library(sqlite3_client STATIC)
target_sources(sqlite3_client PRIVATE src/sqlite3_client.cc
                                      include/sqlite3_client.h)
target_link_libraries(sqlite3_client PRIVATE project_compile_options)
target_include_directories(sqlite3_client PUBLIC include)
target_link_libraries(sqlite3_client PRIVATE sqlite3_queries)
target_link_libraries(sqlite3_client PRIVATE Drogon::Drogon)
target_link_libraries(sqlite3_client PRIVATE utilities)

###########################################
### Minpass
###########################################
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

target_link_libraries(minpass PRIVATE OpenSSL::SSL OpenSSL::Crypto)

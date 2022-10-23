cmake_minimum_required(VERSION 3.24)

project(minpass LANGUAGES CXX)

include(cmake/init.cmake)

###########################################
### Required packages
###########################################
find_package(Drogon CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(fmt CONFIG REQUIRED)

###########################################
### Utilities
###########################################
add_library(utilities STATIC)
target_sources(utilities PRIVATE src/utilities/strong_types.cc
                                 include/utilities/strong_types.h)
target_link_libraries(utilities PRIVATE project_compile_options)
target_include_directories(utilities PUBLIC include)

###########################################
### Minpass types
###########################################
add_library(minpass_types STATIC)
target_sources(minpass_types PRIVATE src/minpass_types.cc
                                     include/minpass_types.h)
target_link_libraries(minpass_types PRIVATE project_compile_options)
target_link_libraries(minpass_types PRIVATE utilities)
target_include_directories(minpass_types PUBLIC include)

###########################################
### Database Abstraction
###########################################
add_library(database_abstraction STATIC)
target_sources(database_abstraction PRIVATE src/database_abstraction.cc
                                            include/database_abstraction.h)
target_link_libraries(database_abstraction PRIVATE project_compile_options)
target_include_directories(database_abstraction PUBLIC include)
target_link_libraries(database_abstraction PRIVATE Drogon::Drogon)
target_link_libraries(database_abstraction PRIVATE minpass_types)
target_link_libraries(database_abstraction PRIVATE fmt::fmt)

###########################################
### SQLite3_Client
###########################################
add_library(sqlite3_client STATIC)
target_sources(
  sqlite3_client
  PRIVATE src/sqlite3_client.cc
          include/sqlite3_client.h
          src/sqlite3_client/helpers.cc
          include/sqlite3_client/helpers.h)
target_link_libraries(sqlite3_client PRIVATE project_compile_options)
target_include_directories(sqlite3_client PUBLIC include)
target_link_libraries(sqlite3_client PRIVATE database_abstraction)
target_link_libraries(sqlite3_client PRIVATE Drogon::Drogon)
target_link_libraries(sqlite3_client PRIVATE minpass_types)
target_link_libraries(sqlite3_client PRIVATE fmt::fmt)

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

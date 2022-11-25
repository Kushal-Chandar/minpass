cmake_minimum_required(VERSION 3.24)

project(minpass LANGUAGES CXX)

include(cmake/init.cmake)

###########################################
### Required packages
###########################################
find_package(Drogon CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)

###########################################
### Utilities
###########################################
add_library(utilities STATIC)
target_sources(utilities PRIVATE src/utilities/strong_types.cc
                                 include/utilities/strong_types.h)
target_link_libraries(utilities PRIVATE project_compile_options)
target_include_directories(utilities PUBLIC include)

###########################################
### Minpass crypto
###########################################
add_library(minpass_crypto)
target_sources(
  minpass_crypto
  PRIVATE include/minpass_crypto.h
          src/minpass_crypto.cc
          include/minpass_crypto/scrypt_kdf.h
          src/minpass_crypto/scrypt_kdf.cc
          include/minpass_crypto/crytopp_conversions.h
          src/minpass_crypto/crytopp_conversions.cc
          include/minpass_crypto/aes_gcm_256.h
          src/minpass_crypto/aes_gcm_256.cc)
target_link_libraries(minpass_crypto PRIVATE project_compile_options)
target_include_directories(minpass_crypto PUBLIC include)
target_link_libraries(minpass_crypto PRIVATE cryptopp::cryptopp)
target_link_libraries(minpass_crypto PRIVATE fmt::fmt)

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
### SQLite3 client
###########################################
add_library(sqlite3_client STATIC)
target_sources(
  sqlite3_client
  PRIVATE src/sqlite3_client.cc
          include/sqlite3_client.h
          src/sqlite3_client/helpers.cc
          include/sqlite3_client/helpers.h
          src/sqlite3_client/request_processor.cc
          include/sqlite3_client/request_processor.h)
target_link_libraries(sqlite3_client PRIVATE project_compile_options)
target_include_directories(sqlite3_client PUBLIC include)
target_link_libraries(sqlite3_client PRIVATE Drogon::Drogon)
target_link_libraries(sqlite3_client PRIVATE minpass_crypto)
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

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
target_link_libraries(utilities PRIVATE project_compile_options)
# target_include_directories()

###########################################
### Minpass crypto
###########################################
add_library(minpass_crypto)
target_link_libraries(minpass_crypto PRIVATE project_compile_options)
target_link_libraries(minpass_crypto PRIVATE cryptopp::cryptopp)
target_link_libraries(minpass_crypto PRIVATE fmt::fmt)

###########################################
### Minpass types
###########################################
add_library(minpass_types STATIC)
target_link_libraries(minpass_types PRIVATE project_compile_options)
target_link_libraries(minpass_types PRIVATE utilities)

###########################################
### SQLite3 client
###########################################
add_library(sqlite3_client STATIC)
target_link_libraries(sqlite3_client PRIVATE project_compile_options)
target_link_libraries(sqlite3_client PRIVATE Drogon::Drogon)
target_link_libraries(sqlite3_client PRIVATE minpass_crypto)
target_link_libraries(sqlite3_client PRIVATE minpass_types)
target_link_libraries(sqlite3_client PRIVATE fmt::fmt)

###########################################
### Minpass
###########################################
target_link_libraries(minpass PRIVATE project_compile_options)
target_link_libraries(minpass PRIVATE configuration_header)
target_link_libraries(minpass PRIVATE sqlite3_client)
target_link_libraries(minpass PRIVATE Drogon::Drogon)
# For drogon compilation to work
# link winsock, winsock2, iphlpapi (Googled for undefined references and link those libraries where they are found)
if(WIN32)
  target_link_libraries(minpass PRIVATE wsock32 ws2_32 iphlpapi)
endif()

#################################################
### adding source files and private headers
#################################################
add_subdirectory(inc)
add_subdirectory(impl)

###########################################
### Required packages
###########################################
find_package(Drogon CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)

###########################################
### Utilities
###########################################
add_library(utilities STATIC)
target_link_libraries(utilities PRIVATE project_compile_options)
target_include_directories(utilities PRIVATE ${MINPASS_PRIVATE_HEADER_DIR})

###########################################
### Minpass cli
###########################################
add_library(cli STATIC)
target_link_libraries(cli PRIVATE project_compile_options)
target_link_libraries(cli PRIVATE CLI11::CLI11)
target_link_libraries(cli PRIVATE configuration_header)
target_link_libraries(cli PRIVATE fmt::fmt)
target_include_directories(cli PRIVATE ${MINPASS_PRIVATE_HEADER_DIR})

###########################################
### Minpass crypto
###########################################
add_library(crypto STATIC)
target_link_libraries(crypto PRIVATE project_compile_options)
target_link_libraries(crypto PRIVATE cryptopp::cryptopp)
target_link_libraries(crypto PRIVATE fmt::fmt)
target_include_directories(crypto PRIVATE ${MINPASS_PRIVATE_HEADER_DIR})

###########################################
### Minpass types
###########################################
add_library(types STATIC)
target_link_libraries(types PRIVATE project_compile_options)
target_link_libraries(types PRIVATE utilities)
target_include_directories(types PRIVATE ${MINPASS_PRIVATE_HEADER_DIR})

###########################################
### SQLite3 client
###########################################
add_library(sqlite3_client STATIC)
target_link_libraries(sqlite3_client PRIVATE project_compile_options)
target_link_libraries(sqlite3_client PRIVATE Drogon::Drogon)
target_link_libraries(sqlite3_client PRIVATE crypto)
target_link_libraries(sqlite3_client PRIVATE types)
target_link_libraries(sqlite3_client PRIVATE fmt::fmt)
target_include_directories(sqlite3_client PRIVATE ${MINPASS_PRIVATE_HEADER_DIR})

###########################################
### Minpass
###########################################
target_link_libraries(minpass PRIVATE project_compile_options)
target_link_libraries(minpass PRIVATE sqlite3_client)
target_link_libraries(minpass PRIVATE Drogon::Drogon)
target_link_libraries(minpass PRIVATE cli)
# For drogon compilation to work
# link winsock, winsock2, iphlpapi (Googled for undefined references and link those libraries where they are found)
if(WIN32)
  target_link_libraries(minpass PRIVATE wsock32 ws2_32 iphlpapi)
endif()
target_include_directories(minpass PRIVATE ${MINPASS_PRIVATE_HEADER_DIR})

#################################################
### adding source files and private headers
#################################################
add_subdirectory(inc)
add_subdirectory(impl)

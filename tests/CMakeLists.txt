###########################################
### Required packages
###########################################
find_package(Drogon CONFIG REQUIRED)

###########################################
### test utilities
###########################################
add_library(test_utilities)

###########################################
### Minpass tests
###########################################
add_executable(tests)
set_target_properties(
  tests
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(tests PRIVATE sqlite3_client)
target_link_libraries(tests PRIVATE crypto)
target_link_libraries(tests PRIVATE test_utilities)
target_link_libraries(tests PRIVATE types)
target_link_libraries(tests PRIVATE utilities)
target_link_libraries(tests PRIVATE Drogon::Drogon)
target_link_libraries(tests PRIVATE coverage_options)
# For drogon compilation to work
# link winsock, winsock2, iphlpapi (Googled for undefined references and link those libraries where they are found)
if(WIN32)
  target_link_libraries(tests PRIVATE wsock32 ws2_32 iphlpapi)
endif()
target_include_directories(tests PRIVATE ${MINPASS_PRIVATE_HEADER_DIR})
target_include_directories(tests PRIVATE test_utilities/include)

###########################################
### Minpass test sources from current dir
###########################################
target_sources(
  tests
  PRIVATE main_test.cc
          crypto_test.cc
          types_test.cc
          sqlite3_client_test.cc)

###########################################
### sources from subdirs
###########################################s
add_subdirectory(utilities)
add_subdirectory(test_utilities)
add_subdirectory(sqlite3_client)
add_subdirectory(crypto)

parseandadddrogontests(tests)

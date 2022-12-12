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
add_executable(minpass_tests)
set_target_properties(
  minpass_tests
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(minpass_tests PRIVATE sqlite3_client)
target_link_libraries(minpass_tests PRIVATE minpass_crypto)
target_link_libraries(minpass_tests PRIVATE test_utilities)
target_link_libraries(minpass_tests PRIVATE minpass_types)
target_link_libraries(minpass_tests PRIVATE utilities)
target_link_libraries(minpass_tests PRIVATE Drogon::Drogon)
target_link_libraries(minpass_tests PRIVATE coverage_options)
# For drogon compilation to work
# link winsock, winsock2, iphlpapi (Googled for undefined references and link those libraries where they are found)
if(WIN32)
  target_link_libraries(minpass_tests PRIVATE wsock32 ws2_32 iphlpapi)
endif()
target_include_directories(minpass_tests PRIVATE ${MINPASS_PRIVATE_HEADER_DIR})
target_include_directories(minpass_tests PRIVATE test_utilities/include)

###########################################
### Minpass test sources from current dir
###########################################
target_sources(
  minpass_tests
  PRIVATE main_test.cc
          minpass_crypto_test.cc
          minpass_types_test.cc
          sqlite3_client_test.cc)

###########################################
### sources from subdirs
###########################################s
add_subdirectory(utilities)
add_subdirectory(test_utilities)
add_subdirectory(sqlite3_client)
add_subdirectory(minpass_crypto)

parseandadddrogontests(minpass_tests)

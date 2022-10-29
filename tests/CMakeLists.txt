###########################################
### Required packages
###########################################
find_package(Drogon CONFIG REQUIRED)

###########################################
### Minpass tests
###########################################
add_executable(
  minpass_tests
  main_test.cc
  minpass_types_test.cc
  sqlite3_client_test.cc
  utilities/strong_types_test.cc
  sqlite3_client/helpers_test.cc)
target_link_libraries(minpass_tests PRIVATE sqlite3_client)
target_link_libraries(minpass_tests PRIVATE minpass_types)
target_link_libraries(minpass_tests PRIVATE utilities)
target_link_libraries(minpass_tests PRIVATE Drogon::Drogon)
target_link_libraries(minpass_tests PRIVATE coverage_options)

# For drogon compilation to work
# link winsock, winsock2, iphlpapi (Googled for undefined references and link those libraries where they are found)
if(WIN32)
  target_link_libraries(minpass_tests PRIVATE wsock32 ws2_32 iphlpapi)
endif()
target_link_libraries(minpass_tests PRIVATE OpenSSL::SSL OpenSSL::Crypto)
parseandadddrogontests(minpass_tests)

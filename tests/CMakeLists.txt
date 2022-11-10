###########################################
### Required packages
###########################################
find_package(Drogon CONFIG REQUIRED)

###########################################
### test utilities
###########################################
add_library(test_utilities test_utilities/include/random_string_generator.h
                           test_utilities/src/random_string_generator.cc)
target_include_directories(test_utilities PUBLIC ${CMAKE_CURRENT_LIST_DIR})

###########################################
### Minpass tests
###########################################
add_executable(
  minpass_tests
  main_test.cc
  minpass_crypto_test.cc
  minpass_types_test.cc
  sqlite3_client_test.cc
  minpass_crypto/aes_gcm_256_test.cc
  minpass_crypto/crytopp_conversions_test.cc
  minpass_crypto/scrypt_kdf_test.cc
  sqlite3_client/helpers_test.cc
  utilities/strong_types_test.cc)
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
parseandadddrogontests(minpass_tests)

include(GoogleTest)

add_executable(hello_test hello_test.cc)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(hello_test PRIVATE GTest::gtest_main coverage_options)

gtest_discover_tests(hello_test) #find all tests in target files

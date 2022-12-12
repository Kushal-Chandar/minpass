###########################################
### test utilities
###########################################
target_include_directories(test_utilities PRIVATE include/test_utilities)
target_sources(test_utilities
               PRIVATE include/test_utilities/random_string_generator.h)

###########################################
### adding sub dirs
###########################################
add_subdirectory(src)

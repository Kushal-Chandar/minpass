#if !defined( \
    MINPASS_TESTS_TEST_UTILITIES_INCLUDE_TEST_UTILITIES_RANDOM_STRING_GENERATOR_H_)
#define MINPASS_TESTS_TEST_UTILITIES_INCLUDE_TEST_UTILITIES_RANDOM_STRING_GENERATOR_H_

#include <random>

namespace minpass::tests {

auto generate_random_string(std::size_t len) -> std::string;

}  // namespace minpass::tests

#endif  // MINPASS_TESTS_TEST_UTILITIES_INCLUDE_TEST_UTILITIES_RANDOM_STRING_GENERATOR_H_

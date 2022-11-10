#include "test_utilities/include/random_string_generator.h"

#include <iostream>
#include <random>
#include <string>

namespace minpass::tests {

auto generate_random_string(std::size_t length) -> std::string {
  std::random_device rng;
  std::seed_seq seed{rng(), rng(), rng(), rng(), rng(), rng(), rng(), rng()};
  std::mt19937 rng_eng(seed);

  // ASCII 32 - 126 range for printable chars
  const int kASCIIPrintableStart = 32;
  const int kASCIIPrintableEnd = 126;

  std::uniform_int_distribution distribution(kASCIIPrintableStart,
                                             kASCIIPrintableEnd);
  std::string random_string;

  for (size_t i = 0; i < length; i++) {
    random_string.push_back(static_cast<char>((distribution(rng_eng))));
  }

  return random_string;
}

}  // namespace minpass::tests

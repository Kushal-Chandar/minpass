#include "cli.h"

#include <drogon/drogon_test.h>  // for run

#include <vector>

DROGON_TEST(MinpassCliTest) {
  // When no command line arguments are given
  std::vector<const char *> argv{"Path to executable"};
  CHECK(minpass::CLI::Parse(1, argv.data()) == std::nullopt);

  // When --help command line arguments is given
  argv.emplace_back("--help");
  CHECK(minpass::CLI::Parse(2, argv.data()) != std::nullopt);
  argv.clear();

  // When -e command line arguments is given
  argv.emplace_back("-e");
  CHECK(minpass::CLI::Parse(2, argv.data()) != std::nullopt);
  argv.clear();

  // When both command line arguments are given (if --help is given help should
  // print first)
  argv.emplace_back("-v");
  argv.emplace_back("--help");
  CHECK(minpass::CLI::Parse(3, argv.data()) != std::nullopt);
}

auto main(int argc, char *argv[]) -> int {
  return drogon::test::run(argc, argv);
}

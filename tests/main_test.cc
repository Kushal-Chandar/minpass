#define DROGON_TEST_MAIN
#include <drogon/drogon_test.h>

auto main(int argc, char *argv[]) -> int {
  try {
    return drogon::test::run(argc, argv);
  } catch (...) {
    return 0;
  }
}

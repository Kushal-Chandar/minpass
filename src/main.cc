#include <drogon/drogon.h>

auto main() -> int {
  drogon::app().loadConfigFile("./server_config.json").run();
  return EXIT_SUCCESS;
}

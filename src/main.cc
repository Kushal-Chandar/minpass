#include <drogon/drogon.h>
#include <fmt/core.h>

#include <chrono>
#include <fstream>

auto main() -> int {
  drogon::app().loadConfigFile("./server_config.json").run();
  return EXIT_SUCCESS;
}

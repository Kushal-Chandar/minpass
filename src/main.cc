#include <drogon/drogon.h>

#include "sqlite3_client.h"

auto main() -> int {
  drogon::app().loadConfigFile("./server_config.json").run();
  return EXIT_SUCCESS;
}

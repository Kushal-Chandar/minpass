#include <drogon/HttpAppFramework.h>  // for app, HttpAppFramework
#include <stdlib.h>                   // for EXIT_SUCCESS

#include "sqlite3_client.h"

auto main() -> int {
  drogon::app().loadConfigFile("./server_config.json").run();
  return EXIT_SUCCESS;
}

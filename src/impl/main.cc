#include <drogon/HttpAppFramework.h>  // for app, HttpAppFramework
#include <fmt/color.h>

#include <cstdlib>  // for EXIT_SUCCESS

#include "cli.h"
#include "sqlite3_client.h"

auto main(int argc, char const* argv[]) -> int {
  auto optional = minpass::CLI::Parse(argc, argv);
  if (optional.has_value()) {
    return optional.value();
  }

  int exit_code{};
  try {
    drogon::app().loadConfigFile("./server_config.json").run();
    // exit_code = EXIT_SUCCESS; //code already intialised with 0;
  } catch (const std::exception& error) {
    fmt::print(
        fmt::fg(fmt::color::red),
        "{}.\nConfiguration cannot be loaded\n. Please grab the file from the "
        "Github repo.\n",
        error.what());
    exit_code = EXIT_FAILURE;
  }
  return exit_code;
}

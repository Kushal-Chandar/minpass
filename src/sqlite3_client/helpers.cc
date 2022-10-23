#include "sqlite3_client/helpers.h"

auto minpass::sqlite3_client::exception(
    const drogon::orm::DrogonDbException &error) -> void {
  fmt::print(fmt::fg(fmt::color::red), "error: {}\n", error.base().what());
}

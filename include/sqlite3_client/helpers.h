#if !defined(SQLITE3_HELPERS)
#define SQLITE3_HELPERS

#include <drogon/drogon.h>
#include <fmt/color.h>
#include <fmt/core.h>

namespace minpass::sqlite3_client {

auto exception(const drogon::orm::DrogonDbException &error) -> void;
auto no_result_callback() -> void;

}  // namespace minpass::sqlite3_client

#endif  // SQLITE3_HELPERS

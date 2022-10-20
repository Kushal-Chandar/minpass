#if !defined(SQLITE3_QUERIES)
#define SQLITE3_QUERIES

#include <drogon/drogon.h>

namespace minpass {
class SQLite3Queries {
  auto CreateTable(std::string_view) -> void;
  auto InsertPassword(std::string_view, std::string_view, std::string_view,
                      std::string_view) -> void;
  auto RetrievePassword(std::string_view) -> void;
};
}  // namespace minpass

#endif  // SQLITE3_QUERIES

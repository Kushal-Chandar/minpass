#if !defined(SQLITE3_QUERIES)
#define SQLITE3_QUERIES

#include <drogon/drogon.h>

#include "minpass_types.h"

namespace minpass {
class SQLite3Queries {
  auto CreateTable(std::string_view name) -> void;
  auto InsertPassword(Website& website, Email& email, Username&, Password&)
      -> void;
  auto RetrievePassword(Website& website) -> void;
};
}  // namespace minpass

#endif  // SQLITE3_QUERIES

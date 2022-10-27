#if !defined(SQLite3_Queries)
#define SQLite3_Queries

#include <__fwd/string_view.h>  // for string_view

#include <iosfwd>       // for string
#include <string_view>  // for basic_string_view

#include "minpass_types.h"  // for Website, Email, Password, Username

namespace minpass {
class SQLite3Queries {
 public:
  SQLite3Queries(std::string_view table_name = "minpass");
  auto CreateTableQuery() -> std::string;
  auto CreatePasswordQuery(Website& website, Email& email, Username& username,
                           Password& password) -> std::string;
  auto ReadPasswordQuery(Website& website) -> std::string;
  auto UpdatePasswordQuery(Website& website, Email& email, Username& username,
                           Password& password) -> std::string;
  auto DeletePasswordQuery(Website& website) -> std::string;

 private:
  std::string table_name_;
};

}  // namespace minpass

#endif  // SQLite3_Queries

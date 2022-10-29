#if !defined(SQLite3_Queries)
#define SQLite3_Queries

#include <iosfwd>       // for string
#include <string_view>  // for basic_string_view

#include "minpass_types.h"  // for Website, Email, Password, Username

namespace minpass {
class SQLite3Queries {
 public:
  explicit SQLite3Queries(std::string_view table_name = "minpass");
  auto CreateTableQuery() -> std::string;
  auto CreatePasswordQuery(const Website& website, const Email& email,
                           const Username& username, const Password& password)
      -> std::string;
  auto ReadPasswordQuery(const Website& website) -> std::string;
  auto UpdatePasswordQuery(const Website& website, const Email& email,
                           const Username& username, const Password& password)
      -> std::string;
  auto DeletePasswordQuery(const Website& website) -> std::string;

 private:
  std::string table_name_;
};

}  // namespace minpass

#endif  // SQLite3_Queries

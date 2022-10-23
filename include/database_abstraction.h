#if !defined(DATABASE_ABSTRACTION)
#define DATABASE_ABSTRACTION

#include <drogon/drogon.h>

#include "minpass_types.h"

namespace minpass {
class DatabaseAbstraction {
 public:
  DatabaseAbstraction(std::string_view table_name = "minpass");
  auto CreateTableQuery() -> std::string;
  auto InsertPasswordQuery(Website& website, Email& email, Username& username,
                           Password& password) -> std::string;
  auto RetrievePasswordQuery(Website& website) -> std::string;
  auto DeletePasswordQuery(Website& website) -> std::string;

 private:
  std::string table_name_;
};

}  // namespace minpass

#endif  // DATABASE_ABSTRACTION

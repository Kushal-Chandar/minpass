#if !defined(DATABASE_ABSTRACTION)
#define DATABASE_ABSTRACTION

#include <drogon/drogon.h>

#include "minpass_types.h"

namespace minpass {
class DatabaseAbstraction {
 public:
  DatabaseAbstraction(std::string_view table_name = "minpass");
  auto InsertPassword(Website& website, Email& email, Username&, Password&)
      -> void;
  auto RetrievePassword(Website& website) -> Json::Value;

 private:
  auto CreateTable() -> void;
  std::string_view table_name_;
};
}  // namespace minpass

#endif  // DATABASE_ABSTRACTION

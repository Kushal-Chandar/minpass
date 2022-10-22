#if !defined(DATABASE_ABSTRACTION)
#define DATABASE_ABSTRACTION

#include <drogon/drogon.h>

#include "minpass_types.h"

namespace minpass {
class DatabaseAbstraction {
 public:
  DatabaseAbstraction(DatabaseName database_name = "minpass",
                      TableName table_name = "minpass");
  auto InsertPassword(Website& website, Email& email, Username&, Password&)
      -> std::shared_ptr<Json::Value>;
  auto RetrievePassword(Website& website) -> std::shared_ptr<Json::Value>;
  auto DeletePassword(Website& website) -> std::shared_ptr<Json::Value>;

 private:
  auto CreateTable() -> void;
  auto CreateTableQuery() -> std::string;
  auto InsertPasswordQuery(Website& website, Email& email, Username& username,
                           Password& password) -> std::string;
  auto RetrievePasswordQuery(Website& website) -> std::string;
  auto DeletePasswordQuery(Website& website) -> std::string;
  std::string table_name_;
  drogon::orm::DbClientPtr client_;
};
}  // namespace minpass

#endif  // DATABASE_ABSTRACTION

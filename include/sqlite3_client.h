#if !defined(MINPASS)
#define MINPASS

#include <drogon/drogon.h>

#include "database_abstraction.h"
#include "minpass_types.h"

namespace minpass {
class SQLite3Client : public drogon::HttpController<SQLite3Client> {
 public:
  METHOD_LIST_BEGIN
  METHOD_ADD(SQLite3Client::SetPassword, "/website={}", drogon::Post);
  METHOD_ADD(SQLite3Client::GetPassword, "/website={}", drogon::Get);
  METHOD_ADD(SQLite3Client::RemovePassword, "/website={}", drogon::Delete);
  METHOD_LIST_END

  SQLite3Client(const std::string &database_name = "minpass");

  auto SetPassword(
      [[maybe_unused]] const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback,
      Website website /* , Email email, Username username, Password password */)
      -> void;
  auto GetPassword(
      [[maybe_unused]] const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback,
      Website website) -> void;
  auto RemovePassword(
      [[maybe_unused]] const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback,
      Website website) -> void;

 private:
  DatabaseAbstraction db_abs_;
  drogon::orm::DbClientPtr client_;
  auto CreateTable() -> void;
};

}  // namespace minpass

#endif  // MINPASS

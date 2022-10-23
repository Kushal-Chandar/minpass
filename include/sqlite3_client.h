#if !defined(MINPASS)
#define MINPASS

#include <drogon/drogon.h>

#include "minpass_types.h"
#include "sqlite3_queries.h"

namespace minpass {
class SQLite3Client : public drogon::HttpController<SQLite3Client> {
 public:
  METHOD_LIST_BEGIN
  METHOD_ADD(SQLite3Client::SetPasswordData, "/website={}", drogon::Post);
  METHOD_ADD(SQLite3Client::GetPasswordData, "/website={}", drogon::Get);
  METHOD_ADD(SQLite3Client::RemovePasswordData, "/website={}", drogon::Delete);
  METHOD_ADD(SQLite3Client::ModifyPasswordData, "/website={}", drogon::Patch);
  METHOD_LIST_END

  explicit SQLite3Client(const std::string &database_name = "minpass");

  auto SetPasswordData(
      [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
      std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
      Website website) -> void;
  auto GetPasswordData(
      [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
      std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
      Website website) -> void;
  auto RemovePasswordData(
      [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
      std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
      Website website) -> void;
  auto ModifyPasswordData(
      [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
      std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
      Website website) -> void;

 private:
  SQLite3Queries query_factory_;
  drogon::orm::DbClientPtr client_;
  auto CreateTable() -> void;
  static auto MakeSuccessResponse() -> drogon::HttpResponsePtr;
};

}  // namespace minpass

#endif  // MINPASS

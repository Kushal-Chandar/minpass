#if !defined(MINPASS)
#define MINPASS

#include <drogon/drogon.h>  // for app, HttpAppFramework
#include <json/value.h>     // for Value

#include <iostream>  // for char_traits, operator<<
#include <tuple>     // for tuple_element<>::type

#include "minpass_types.h"  // for Website
#include "sqlite3_client.h"
#include "sqlite3_client/helpers.h"  // for Helpers
#include "sqlite3_queries.h"         // for SQLite3Queries

namespace minpass {
class SQLite3Client : public drogon::HttpController<SQLite3Client> {
 public:
  METHOD_LIST_BEGIN
  METHOD_ADD(SQLite3Client::SetPasswordData, "/website={}", drogon::Post);
  METHOD_ADD(SQLite3Client::GetPasswordData, "/website={}", drogon::Get);
  METHOD_ADD(SQLite3Client::RemovePasswordData, "/website={}", drogon::Delete);
  METHOD_ADD(SQLite3Client::ModifyPasswordData, "/website={}", drogon::Patch);
  METHOD_ADD(SQLite3Client::QuitServer, "/stop", drogon::Get);
  METHOD_LIST_END

  explicit SQLite3Client(const std::string &database_name = "minpass");

  auto SetPasswordData(
      [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
      std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
      const Website &website) -> void;
  auto GetPasswordData(
      [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
      std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
      const Website &website) -> void;
  auto RemovePasswordData(
      [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
      std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
      const Website &website) -> void;
  auto ModifyPasswordData(
      [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
      std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
      const Website &website) -> void;
  static auto QuitServer(
      [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
      std::function<void(const drogon::HttpResponsePtr &)> &&http_callback)
      -> void;

 private:
  SQLite3Queries query_factory_;
  drogon::orm::DbClientPtr client_;
};

}  // namespace minpass

#endif  // MINPASS

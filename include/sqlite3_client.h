#if !defined(MINPASS_INCLUDE_SQLITE3_CLIENT_H_)
#define MINPASS_INCLUDE_SQLITE3_CLIENT_H_

#include <drogon/HttpController.h>    // for METHOD_ADD, HttpController, MET...
#include <drogon/HttpResponse.h>      // for HttpResponsePtr
#include <drogon/HttpTypes.h>         // for Get, Delete, Patch, Post
#include <drogon/drogon_callbacks.h>  // for HttpRequestPtr
#include <drogon/orm/DbClient.h>      // for DbClientPtr

#include <functional>  // for function
#include <iostream>    // for string

#include "minpass_types.h"  // for Website

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

  explicit SQLite3Client(
      const DatabaseName &database_name = DatabaseName("minpass"),
      TableName table_name = TableName("minpass"));

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
  drogon::orm::DbClientPtr client_;
  TableName table_name_;
};

}  // namespace minpass

#endif  // MINPASS_INCLUDE_SQLITE3_CLIENT_H_

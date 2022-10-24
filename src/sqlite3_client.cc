#include "sqlite3_client.h"

#include <drogon/drogon.h>

#include "minpass_types.h"
#include "sqlite3_client/helpers.h"
#include "sqlite3_queries.h"

namespace minpass {

SQLite3Client::SQLite3Client(const std::string &database_name) {
  client_ = drogon::app().getDbClient(database_name);
  sqlite3_client::Helpers::CreatePasswordTable(
      client_, query_factory_.CreateTableQuery());
}

auto SQLite3Client::SetPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    Website website) -> void {
  Json::Value response_object;

  auto request_json_ptr = sqlite3_client::Helpers::ValidateRequest(
      http_request, std::forward<decltype(http_callback)>(http_callback),
      response_object);

  Email email;
  Username username;
  Password password;
  sqlite3_client::Helpers::ParseJsonRequest(request_json_ptr, email, username,
                                            password);

  auto sql_query =
      query_factory_.CreatePasswordQuery(website, email, username, password);
  auto call_back = []([[maybe_unused]] const drogon::orm::Result &result) {};
  client_->execSqlAsync(sql_query, call_back,
                        sqlite3_client::Helpers::CommonExceptionCatch);

  response_object["message"] = "ok";
  http_callback(sqlite3_client::Helpers::MakeResponse(response_object));
}

auto SQLite3Client::GetPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    Website website) -> void {
  auto sql_query = query_factory_.ReadPasswordQuery(website);
  client_->execSqlAsync(
      sql_query,
      [http_callback]([[maybe_unused]] const drogon::orm::Result &result) {
        Json::Value response_object;
        drogon::HttpStatusCode status_code = drogon::k404NotFound;
        response_object["message"] = "website not found";
        if (!result.empty()) {
          auto first_row = result[0];
          status_code = drogon::k200OK;
          response_object["message"] = "ok";
          response_object["website"] = first_row["website"].as<std::string>();
          response_object["email"] = first_row["email"].as<std::string>();
          response_object["username"] = first_row["username"].as<std::string>();
          response_object["password"] = first_row["password"].as<std::string>();
        }
        http_callback(sqlite3_client::Helpers::MakeResponse(response_object,
                                                            status_code));
      },
      sqlite3_client::Helpers::CommonExceptionCatch);
}

auto SQLite3Client::ModifyPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    Website website) -> void {
  Json::Value response_object;

  auto request_json_ptr = sqlite3_client::Helpers::ValidateRequest(
      http_request, std::forward<decltype(http_callback)>(http_callback),
      response_object);

  Email email;
  Username username;
  Password password;
  sqlite3_client::Helpers::ParseJsonRequest(request_json_ptr, email, username,
                                            password);

  auto sql_query =
      query_factory_.UpdatePasswordQuery(website, email, username, password);
  auto call_back = []([[maybe_unused]] const drogon::orm::Result &result) {};
  client_->execSqlAsync(sql_query, call_back,
                        sqlite3_client::Helpers::CommonExceptionCatch);

  response_object["message"] = "ok";
  http_callback(
      sqlite3_client::Helpers::MakeResponse(response_object, drogon::k200OK));
}

auto SQLite3Client::RemovePasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    Website website) -> void {
  Json::Value response_object;
  auto sql_query = query_factory_.DeletePasswordQuery(website);
  auto call_back = []([[maybe_unused]] const drogon::orm::Result &result) {};
  client_->execSqlAsync(sql_query, call_back,
                        sqlite3_client::Helpers::CommonExceptionCatch);
  response_object["message"] = "ok";
  http_callback(
      sqlite3_client::Helpers::MakeResponse(response_object, drogon::k200OK));
}

}  // namespace minpass

#include "sqlite3_client.h"

#include <drogon/drogon.h>

#include "minpass_types.h"
#include "sqlite3_client/helpers.h"
#include "sqlite3_queries.h"

namespace minpass {

SQLite3Client::SQLite3Client(const std::string &database_name) {
  client_ = drogon::app().getDbClient(database_name);
  CreateTable();
}

auto SQLite3Client::CreateTable() -> void {
  auto sql_query = query_factory_.CreateTableQuery();
  auto call_back = []([[maybe_unused]] const drogon::orm::Result &result) {};
  client_->execSqlAsync(sql_query, call_back,
                        minpass::sqlite3_client::exception);
}

auto SQLite3Client::MakeSuccessResponse() -> drogon::HttpResponsePtr {
  Json::Value response_object;
  response_object["result"] = "ok";
  auto http_response =
      drogon::HttpResponse::newHttpJsonResponse(response_object);
  return http_response;
}

auto SQLite3Client::SetPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    Website website) -> void {
  auto json = http_request->getJsonObject();
  if (!json) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k400BadRequest);
    http_callback(resp);
    return;
  }

  auto email = Email((*json)["email"].asString());
  auto username = Username((*json)["username"].asString());
  auto password = Password((*json)["password"].asString());

  auto sql_query =
      query_factory_.CreatePasswordQuery(website, email, username, password);
  auto call_back = []([[maybe_unused]] const drogon::orm::Result &result) {};
  client_->execSqlAsync(sql_query, call_back,
                        minpass::sqlite3_client::exception);
  http_callback(MakeSuccessResponse());
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
        response_object["result"] = "not found";
        if (!result.empty()) {
          auto first_row = result[0];
          response_object["result"] = "ok";
          response_object["website"] = first_row["website"].as<std::string>();
          response_object["email"] = first_row["email"].as<std::string>();
          response_object["username"] = first_row["username"].as<std::string>();
          response_object["password"] = first_row["password"].as<std::string>();
        }
        auto http_response =
            drogon::HttpResponse::newHttpJsonResponse(response_object);
        http_callback(http_response);
      },
      minpass::sqlite3_client::exception);
}

auto SQLite3Client::ModifyPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    Website website) -> void {
  auto json = http_request->getJsonObject();
  if (!json) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k400BadRequest);
    http_callback(resp);
    return;
  }

  auto email = Email((*json)["email"].asString());
  auto username = Username((*json)["username"].asString());
  auto password = Password((*json)["password"].asString());

  auto sql_query =
      query_factory_.UpdatePasswordQuery(website, email, username, password);
  auto call_back = []([[maybe_unused]] const drogon::orm::Result &result) {};
  client_->execSqlAsync(sql_query, call_back,
                        minpass::sqlite3_client::exception);
  http_callback(MakeSuccessResponse());
}

auto SQLite3Client::RemovePasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    Website website) -> void {
  auto sql_query = query_factory_.DeletePasswordQuery(website);
  auto call_back = []([[maybe_unused]] const drogon::orm::Result &result) {};
  client_->execSqlAsync(sql_query, call_back,
                        minpass::sqlite3_client::exception);
  http_callback(MakeSuccessResponse());
}

}  // namespace minpass

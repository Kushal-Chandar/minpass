#include "sqlite3_client.h"

#include <drogon/drogon.h>

#include "database_abstraction.h"
#include "minpass_types.h"
#include "sqlite3_client/helpers.h"

namespace minpass {

SQLite3Client::SQLite3Client(const std::string &database_name) {
  client_ = drogon::app().getDbClient(database_name);
  CreateTable();
}

auto SQLite3Client::CreateTable() -> void {
  auto sql_query = db_abs_.CreateTableQuery();
  auto call_back = []([[maybe_unused]] bool isNull) {};
  *client_ << sql_query >> call_back >> minpass::sqlite3_client::exception;
}

auto SQLite3Client::SetPassword(
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

  auto response = std::make_shared<Json::Value>();
  auto sql_query =
      db_abs_.InsertPasswordQuery(website, email, username, password);

  auto call_back = [http_callback]([[maybe_unused]] bool isNull) {
    Json::Value response;
    response["result"] = "ok";
    auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
    resp->setStatusCode(drogon::k201Created);
    http_callback(resp);
  };
  *client_ << sql_query >> call_back >> minpass::sqlite3_client::exception;
}

auto SQLite3Client::GetPassword(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    Website website) -> void {
  auto sql_query = db_abs_.RetrievePasswordQuery(website);
  auto call_back = [http_callback]([[maybe_unused]] bool isNull,
                                   Website website, Email email,
                                   Username username, Password password) {
    if (isNull) {
      return;
    }
    Json::Value response;
    response["username"] = username.get();
    response["email"] = email.get();
    response["password"] = password.get();
    response["result"] = "ok";
    response["website"] = website.get();
    auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
    http_callback(resp);
  };
  *client_ << sql_query >> call_back >> minpass::sqlite3_client::exception;
}

auto SQLite3Client::RemovePassword(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    Website website) -> void {
  auto response = std::make_shared<Json::Value>();
  auto sql_query = db_abs_.DeletePasswordQuery(website);
  auto call_back = [http_callback]([[maybe_unused]] bool isNull) {
    Json::Value response;
    response["result"] = "ok";
    auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
    http_callback(resp);
  };
  *client_ << sql_query >> call_back >> minpass::sqlite3_client::exception;
}

}  // namespace minpass

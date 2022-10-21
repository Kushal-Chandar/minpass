#include "sqlite3_client.h"

#include <drogon/drogon.h>
#include <fmt/core.h>

#include "database_abstraction.h"
#include "minpass_types.h"

namespace minpass {

SQLite3Client::SQLite3Client() : db_abs("minpass") {}

auto SQLite3Client::SetPassword(
    const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    Website website, Email email, Username username, Password password)
    -> void {
  fmt::print("{}", req->body());
  db_abs.InsertPassword(website, email, username, password);
  Json::Value response{};
  response["result"] = "ok";
  response["token"] = drogon::utils::getUuid();
  auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}

auto SQLite3Client::GetPassword(
    const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    Website website) -> void {
  fmt::print("{}", req->body());
  // callback()
  Json::Value response = db_abs.RetrievePassword(website);
  response["result"] = "ok";
  auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}

}  // namespace minpass

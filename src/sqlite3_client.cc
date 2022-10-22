#include "sqlite3_client.h"

#include <drogon/drogon.h>
#include <fmt/core.h>

#include "database_abstraction.h"
#include "minpass_types.h"

namespace minpass {

auto SQLite3Client::SetPassword(
    [[maybe_unused]] const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    Website website /* , Email email, Username username, Password password */)
    -> void {
  auto json = req->getJsonObject();
  if (!json) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k400BadRequest);
    callback(resp);
    return;
  }
  auto email = Email((*json)["email"].asString());
  auto username = Username((*json)["username"].asString());
  auto password = Password((*json)["password"].asString());
  auto response = *db_abs_.InsertPassword(website, email, username, password);
  auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
  resp->setStatusCode(drogon::k201Created);
  callback(resp);
}

auto SQLite3Client::GetPassword(
    [[maybe_unused]] const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    Website website) -> void {
  Json::Value response = *db_abs_.RetrievePassword(website);
  auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}

auto SQLite3Client::RemovePassword(
    [[maybe_unused]] const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    Website website) -> void {
  Json::Value response = *db_abs_.DeletePassword(website);
  auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}

}  // namespace minpass

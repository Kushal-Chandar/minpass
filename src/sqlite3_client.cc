#include "sqlite3_client.h"

#include <drogon/drogon.h>
#include <fmt/core.h>

#include "database_abstraction.h"
#include "minpass_types.h"

namespace minpass {

SQLite3Client::SQLite3Client() : db_abs("minpass") {}

auto SQLite3Client::SetPassword(
    [[maybe_unused]] const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    Website website /* , Email email, Username username, Password password */)
    -> void {
  auto json = req->getJsonObject();

  if (!json) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setBody("missing 'value' in body");
    resp->setStatusCode(drogon::k400BadRequest);
    callback(resp);
    return;
  }

  Email email((*json)["email"].asString());
  Username username((*json)["username"].asString());
  Password password((*json)["password"].asString());

  fmt::print("{}-{}-{}-{}\n", website.get(), email.get(), username.get(),
             password.get());

  db_abs.InsertPassword(website, email, username, password);
  Json::Value response{};
  response["result"] = "ok";
  response["token"] = drogon::utils::getUuid();
  auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}

auto SQLite3Client::GetPassword(
    [[maybe_unused]] const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    Website website) -> void {
  Json::Value response = *db_abs.RetrievePassword(website);
  response["result"] = "ok";
  auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}

auto SQLite3Client::RemovePassword(
    [[maybe_unused]] const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    Website website) -> void {
  db_abs.DeletePassword(website);
  Json::Value response{};
  response["result"] = "ok";
  auto resp = drogon::HttpResponse::newHttpJsonResponse(response);
  callback(resp);
}

}  // namespace minpass

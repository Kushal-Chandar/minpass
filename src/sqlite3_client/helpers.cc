#include "sqlite3_client/helpers.h"

#include <__type_traits/remove_extent.h>  // for remove_extent_t
#include <drogon/HttpAppFramework.h>
#include <drogon/orm/Exception.h>  // for DrogonDbException
#include <fmt/color.h>             // for fg, print, color, color::red
#include <fmt/core.h>              // for basic_string_view
#include <fmt/format.h>            // for buffer::append
#include <json/value.h>            // for Value

#include <exception>  // for exception

namespace drogon::orm {
class Result;
}  // namespace drogon::orm

namespace minpass::sqlite3_client {

auto Helpers::CommonExceptionCatch(const drogon::orm::DrogonDbException &error)
    -> void {
  fmt::print(fmt::fg(fmt::color::red), "error: {}\n", error.base().what());
}

auto Helpers::CreatePasswordTable(drogon::orm::DbClientPtr &client,
                                  const std::string &sql_query) -> void {
  auto call_back = []([[maybe_unused]] const drogon::orm::Result &result) {};
  client->execSqlAsync(sql_query, call_back, Helpers::CommonExceptionCatch);
}

auto Helpers::MakeResponse(Json::Value &response_object,
                           drogon::HttpStatusCode status_code)
    -> drogon::HttpResponsePtr {
  auto http_response =
      drogon::HttpResponse::newHttpJsonResponse(response_object);
  http_response->setStatusCode(status_code);
  return http_response;
}

auto Helpers::ValidateRequest(
    const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    Json::Value &response_object_out) -> std::shared_ptr<Json::Value> {
  auto json = http_request->getJsonObject();
  if (!json) {
    response_object_out["message"] = "could not parse request";
    http_callback(MakeResponse(response_object_out, drogon::k400BadRequest));
  }
  return json;
}

auto Helpers::ParseJsonRequest(
    const std::shared_ptr<Json::Value> &validated_json, Email &email_out,
    Username &username_out, Password &password_out) -> void {
  if (validated_json) {
    email_out = Email((*validated_json)["email"].asString());
    username_out = Username((*validated_json)["username"].asString());
    password_out = Password((*validated_json)["password"].asString());
  }
}

}  // namespace minpass::sqlite3_client

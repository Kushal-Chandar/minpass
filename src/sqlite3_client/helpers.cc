#include "sqlite3_client/helpers.h"

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
    Json::Value &response_object) -> std::shared_ptr<Json::Value> {
  auto json = http_request->getJsonObject();
  if (!json) {
    response_object["message"] = "could not parse request";
    http_callback(MakeResponse(response_object, drogon::k400BadRequest));
  }
  return json;
}

}  // namespace minpass::sqlite3_client

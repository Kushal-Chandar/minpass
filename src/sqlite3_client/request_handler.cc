#include "sqlite3_client/request_handler.h"

#include <drogon/HttpRequest.h>

#include "sqlite3_client/helpers.h"

namespace minpass::sqlite3_client {

auto RequestHandler::ParseRequestJson(
    const drogon::HttpRequestPtr &http_request,
    drogon::HttpResponsePtr &http_response, Json::Value &response_object_out)
    -> std::tuple<bool, Email, Username, Password> {
  auto json = http_request->getJsonObject();
  if (!json) {
    response_object_out["message"] = "could not parse request";
    http_response =
        Helpers::MakeResponse(response_object_out, drogon::k400BadRequest);
    return {false, Email(), Username(), Password()};
  }
  response_object_out["message"] = "ok";
  http_response =
      Helpers::MakeResponse(response_object_out, drogon::k202Accepted);

  return {
      true,
      Email(((*json)["email"].asString())),
      Username(((*json)["username"].asString())),
      Password(((*json)["password"].asString())),
  };
}
}  // namespace minpass::sqlite3_client

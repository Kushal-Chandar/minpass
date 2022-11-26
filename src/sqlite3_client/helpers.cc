#include "sqlite3_client/helpers.h"

#include <drogon/HttpRequest.h>           // for HttpRequestPtr
#include <drogon/HttpResponse.h>          // for HttpResponse
#include <drogon/orm/Exception.h>         // for DrogonDbException
#include <drogon/utils/FunctionTraits.h>  // for HttpResponsePtr
#include <fmt/color.h>                    // for fg, print, color, color::red
#include <fmt/format.h>                   // for buffer::append
#include <json/value.h>                   // for Value

#include <exception>  // for exception

#include "minpass_crypto.h"
namespace drogon::orm {
class Result;
}  // namespace drogon::orm

namespace minpass::sqlite3_client {

auto Helpers::CommonExceptionCatch(const drogon::orm::DrogonDbException &error)
    -> void {
  fmt::print(fmt::fg(fmt::color::red), "error: {}\n", error.base().what());
}

auto Helpers::EmptyCallback([[maybe_unused]] const drogon::orm::Result &result)
    -> void {}

auto Helpers::MakeResponse(Json::Value &response_object,
                           drogon::HttpStatusCode status_code)
    -> drogon::HttpResponsePtr {
  auto http_response =
      drogon::HttpResponse::newHttpJsonResponse(response_object);
  http_response->setStatusCode(status_code);
  return http_response;
}

}  // namespace minpass::sqlite3_client

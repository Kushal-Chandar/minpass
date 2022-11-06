#if !defined(MINPASS_INCLUDE_SQLITE3_CLIENT_HELPERS_H_)
#define MINPASS_INCLUDE_SQLITE3_CLIENT_HELPERS_H_

#include <drogon/HttpTypes.h>         // for k200OK, HttpStatusCode
#include <drogon/drogon_callbacks.h>  // for HttpResponsePtr, HttpRequestPtr

#include <tuple>  // for tuple

#include "minpass_types.h"  // for Email, Password, Username
namespace Json {
class Value;
}  // namespace Json
namespace drogon::orm {
class DrogonDbException;
class Result;
}  // namespace drogon::orm

namespace minpass::sqlite3_client {

class Helpers {
 public:
  static auto CommonExceptionCatch(const drogon::orm::DrogonDbException &error)
      -> void;
  static auto EmptyCallback([[maybe_unused]] const drogon::orm::Result &result)
      -> void;
  static auto MakeResponse(Json::Value &response_object,
                           drogon::HttpStatusCode status_code = drogon::k200OK)
      -> drogon::HttpResponsePtr;
  static auto ValidateRequest(const drogon::HttpRequestPtr &http_request,
                              drogon::HttpResponsePtr &http_response,
                              Json::Value &response_object_out)
      -> std::tuple<bool, Email, Username, Password>;
};

}  // namespace minpass::sqlite3_client

#endif  // MINPASS_INCLUDE_SQLITE3_CLIENT_HELPERS_H_

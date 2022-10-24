#if !defined(SQLITE3_CLIENT_HELPERS)
#define SQLITE3_CLIENT_HELPERS

#include <drogon/drogon.h>
#include <fmt/color.h>
#include <fmt/core.h>

#include "minpass_types.h"

namespace minpass::sqlite3_client {

class Helpers {
 public:
  static auto CommonExceptionCatch(const drogon::orm::DrogonDbException &error)
      -> void;
  static auto CreatePasswordTable(drogon::orm::DbClientPtr &client,
                                  const std::string &sql_query) -> void;
  static auto MakeResponse(Json::Value &response_object,
                           drogon::HttpStatusCode status_code = drogon::k200OK)
      -> drogon::HttpResponsePtr;
  static auto ValidateRequest(
      const drogon::HttpRequestPtr &http_request,
      std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
      Json::Value &response_object_out) -> std::shared_ptr<Json::Value>;
  static auto ParseJsonRequest(std::shared_ptr<Json::Value> &validated_json,
                               Email &email_out, Username &username_out,
                               Password &password_out) -> void;
};

}  // namespace minpass::sqlite3_client

#endif  // SQLITE3_CLIENT_HELPERS

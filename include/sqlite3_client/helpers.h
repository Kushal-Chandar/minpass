#if !defined(SQLITE3_CLIENT_HELPERS)
#define SQLITE3_CLIENT_HELPERS

#include <drogon/drogon.h>
#include <fmt/color.h>
#include <fmt/core.h>

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
      Json::Value &response_object) -> std::shared_ptr<Json::Value>;
};

}  // namespace minpass::sqlite3_client

#endif  // SQLITE3_CLIENT_HELPERS

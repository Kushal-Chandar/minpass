#if !defined(SQLITE3_CLIENT_HELPERS)
#define SQLITE3_CLIENT_HELPERS

#include <__functional/function.h>    // for function
#include <__memory/shared_ptr.h>      // for shared_ptr
#include <drogon/HttpResponse.h>      // for HttpResponsePtr
#include <drogon/HttpTypes.h>         // for k200OK, HttpStatusCode
#include <drogon/drogon_callbacks.h>  // for HttpRequestPtr
#include <drogon/orm/DbClient.h>      // for DbClientPtr

#include <iosfwd>  // for string

#include "minpass_types.h"  // for Email, Password, Username

namespace Json {
class Value;
}  // namespace Json

namespace drogon {
namespace orm {
class DrogonDbException;
}  // namespace orm
}  // namespace drogon

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
  static auto ValidateRequest(const drogon::HttpRequestPtr &http_request,
                              drogon::HttpResponsePtr &http_response,
                              Json::Value &response_object_out)
      -> std::tuple<bool, Email, Username, Password>;
};

}  // namespace minpass::sqlite3_client

#endif  // SQLITE3_CLIENT_HELPERS

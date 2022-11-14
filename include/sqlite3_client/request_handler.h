#if !defined(MINPASS_INCLUDE_SQLITE3_CLIENT_REQUEST_HANDLER_H_)
#define MINPASS_INCLUDE_SQLITE3_CLIENT_REQUEST_HANDLER_H_

#include <drogon/drogon_callbacks.h>  // for HttpResponsePtr, HttpRequestPtr

#include <tuple>  // for tuple

#include "minpass_types.h"  // for Email, Password, Username
namespace Json {
class Value;
}  // namespace Json

namespace minpass::sqlite3_client {

class RequestHandler {
 public:
  static auto ParseRequestJson(const drogon::HttpRequestPtr &http_request,
                               drogon::HttpResponsePtr &http_response,
                               Json::Value &response_object_out)
      -> std::tuple<bool, Email, Username, Password>;
};

}  // namespace minpass::sqlite3_client

#endif  // MINPASS_INCLUDE_SQLITE3_CLIENT_REQUEST_HANDLER_H_

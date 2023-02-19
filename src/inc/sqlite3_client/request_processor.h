#if !defined(MINPASS_SRC_INC_SQLITE3_CLIENT_REQUEST_PROCESSOR_H_)
#define MINPASS_SRC_INC_SQLITE3_CLIENT_REQUEST_PROCESSOR_H_

#include <drogon/drogon_callbacks.h>  // for HttpResponsePtr, HttpRequestPtr
#include <json/value.h>

#include <optional>
#include <tuple>  // for tuple

#include "types.h"  // for Email, Password, Username

namespace minpass::sqlite3_client {

class RequestProcessor {
 public:
  auto getHttpResponsePtr() -> drogon::HttpResponsePtr;
  auto SetPassword() -> void;
  auto GetPassword() -> void;
  auto UpdatePassword() -> void;
  auto RemovePassword() -> void;

 private:
  Json::Value response_object_;
  drogon::HttpResponsePtr http_response_;
};

}  // namespace minpass::sqlite3_client

#endif  // MINPASS_SRC_INC_SQLITE3_CLIENT_REQUEST_PROCESSOR_H_

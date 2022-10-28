#include "sqlite3_client/helpers.h"

#include <drogon/drogon_test.h>    // for Case (ptr only), DROGON_TEST, CHEC...
#include <drogon/orm/Exception.h>  // for DrogonDbException
#include <json/value.h>            // for Value

#include "minpass_types.h"  // for Email, Password, Username

namespace drogon {
class DrObjectBase;
}  // namespace drogon

DROGON_TEST(HelpersTests_CommonExceptionCatch) {
  // Testing
  // 1. CommonExceptionCatch function should not throw
  const drogon::orm::DrogonDbException error;
  CHECK_NOTHROW(minpass::sqlite3_client::Helpers::CommonExceptionCatch(error));
}

DROGON_TEST(HelpersTests_MakeResponse) {
  // Testing
  // 1. MakeResponse function should not throw
  Json::Value json;
  CHECK_NOTHROW(minpass::sqlite3_client::Helpers::MakeResponse(json));
}

DROGON_TEST(HelpersTests_ParseJsonRequest) {
  // Testing
  // 1. ParseJsonRequest function should not throw even if json is null
  Json::Value response_object{};
  const drogon::HttpRequestPtr http_request{};
  drogon::HttpResponsePtr http_response{};

  MANDATE_NOTHROW(minpass::sqlite3_client::Helpers::ValidateRequest(
      http_request, http_response, response_object));
}

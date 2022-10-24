#include "sqlite3_client/helpers.h"

#include <drogon/drogon_test.h>

#include "minpass_types.h"

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
  std::shared_ptr<Json::Value> json;
  minpass::Email email;
  minpass::Username username;
  minpass::Password password;
  MANDATE_NOTHROW(minpass::sqlite3_client::Helpers::ParseJsonRequest(
      json, email, username, password));
}

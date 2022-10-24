#include "sqlite3_client/helpers.h"

#include <drogon/drogon_test.h>

DROGON_TEST(HelpersTests_CommonExceptionCatch) {
  // Testing
  // 1. CommonExceptionCatch function should not throw
  const drogon::orm::DrogonDbException error;
  CHECK_NOTHROW(minpass::sqlite3_client::Helpers::CommonExceptionCatch(error));
}

DROGON_TEST(HelpersTests_MakeResponse) {
  // Testing
  // 1. CommonExceptionCatch function should not throw
  Json::Value json;
  CHECK_NOTHROW(minpass::sqlite3_client::Helpers::MakeResponse(json));
}

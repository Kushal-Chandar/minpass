#include "sqlite3_client/helpers.h"

#include <drogon/HttpRequest.h>    // for HttpRequestPtr
#include <drogon/HttpResponse.h>   // for HttpResponse
#include <drogon/drogon_test.h>    // for Case (ptr only), DROGON_TEST,
#include <drogon/orm/Exception.h>  // for DrogonDbException #include
#include <json/value.h>            // for Value

#include <iostream>

#include "test_utilities/random_string_generator.h"

const int kUsernameLen = 20;
const int kPasswordLen = 30;

DROGON_TEST(HelpersTests_CommonExceptionCatch) {
  // Testing
  // 1. CommonExceptionCatch function should not throw
  const drogon::orm::DrogonDbException error;
  CHECK_NOTHROW(minpass::sqlite3_client::Helpers::CommonExceptionCatch(error));
}

DROGON_TEST(HelpersTests_MakeResponse_ExceptionTest1) {
  // Testing
  // 1. MakeResponse function should not throw
  Json::Value json;
  CHECK_NOTHROW(minpass::sqlite3_client::Helpers::MakeResponse(json));
}

DROGON_TEST(HelpersTests_MakeResponse_ResponseTest1) {
  // Testing
  // 1. MakeResponse should return the right response in case of empty json
  // 2. Returning the correct statusCode
  Json::Value json;
  const drogon::HttpStatusCode status_code = drogon::k200OK;
  auto http_response_test = drogon::HttpResponse::newHttpJsonResponse(json);
  http_response_test->setStatusCode(status_code);

  auto http_response_func =
      minpass::sqlite3_client::Helpers::MakeResponse(json);

  CHECK(http_response_func->body() == http_response_test->body());
  CHECK(http_response_func->statusCode() == http_response_test->statusCode());
}

DROGON_TEST(HelpersTests_MakeResponse_ResponseTest2) {
  // Testing
  // 1. MakeResponse should return the right response in case of non empty json
  // 2. Returning the correct statusCode
  Json::Value json;
  json["message"] = "could not parse json";
  const drogon::HttpStatusCode status_code = drogon::k400BadRequest;
  auto http_response_test = drogon::HttpResponse::newHttpJsonResponse(json);
  http_response_test->setStatusCode(status_code);

  auto http_response_func =
      minpass::sqlite3_client::Helpers::MakeResponse(json, status_code);

  CHECK(http_response_func->body() == http_response_test->body());
  CHECK(http_response_func->statusCode() == http_response_test->statusCode());
}

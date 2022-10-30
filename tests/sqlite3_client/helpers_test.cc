#include "sqlite3_client/helpers.h"

#include <drogon/HttpRequest.h>    // for HttpRequestPtr
#include <drogon/HttpResponse.h>   // for HttpResponse
#include <drogon/drogon_test.h>    // for Case (ptr only), DROGON_TEST,
#include <drogon/orm/Exception.h>  // for DrogonDbException #include
#include <json/value.h>            // for Value

#include <iostream>

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

DROGON_TEST(HelpersTests_ValidateRequest_ExceptionTest) {
  // Testing
  // 1. ParseJsonRequest function should not throw even if json is null
  Json::Value request;
  auto http_request = drogon::HttpRequest::newHttpJsonRequest(request);
  auto http_response = drogon::HttpResponse::newHttpJsonResponse(request);
  Json::Value response_object;

  MANDATE_NOTHROW(minpass::sqlite3_client::Helpers::ValidateRequest(
      http_request, http_response, response_object));
}

DROGON_TEST(HelpersTests_ValidateRequest_ReturnValueTest1) {
  // Testing
  // 1. ParseJsonRequest must return the correct structure bindings when json
  // was parsed

  Json::Value request;
  request["email"] = "mail@mail.com";
  request["password"] = "pas22sls";
  request["username"] = "ksdkfsd";
  auto http_request = drogon::HttpRequest::newHttpJsonRequest(request);
  auto http_response = drogon::HttpResponse::newHttpJsonResponse(request);
  Json::Value response_object;

  auto [is_valid, email, username, password] =
      minpass::sqlite3_client::Helpers::ValidateRequest(
          http_request, http_response, response_object);

  CHECK(is_valid == true);
  CHECK(email.get() == request["email"]);
  CHECK(password.get() == request["password"]);
  CHECK(username.get() == request["username"]);
  CHECK(http_response->statusCode() == drogon::k202Accepted);
}

DROGON_TEST(HelpersTests_ValidateRequest_ReturnValueTest2) {
  // Testing
  // 1. ParseJsonRequest must return empty structure bindings when json
  // was not parsed

  Json::Value request;
  Json::String errors;
  auto illegal_raw_request = std::string("{\"email\": \"emai}");

  const Json::CharReaderBuilder builder;
  const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
  reader->parse(illegal_raw_request.data(),
                illegal_raw_request.data() + illegal_raw_request.size(),
                &request, &errors);
  auto http_request = drogon::HttpRequest::newHttpJsonRequest(request);
  auto http_response = drogon::HttpResponse::newHttpResponse();
  Json::Value response_object;

  auto [is_valid, email, username, password] =
      minpass::sqlite3_client::Helpers::ValidateRequest(
          http_request, http_response, response_object);

  CHECK(is_valid == false);
  CHECK(email.get() == "");
  CHECK(password.get() == "");
  CHECK(username.get() == "");
  CHECK(http_response->statusCode() == drogon::k400BadRequest);
}

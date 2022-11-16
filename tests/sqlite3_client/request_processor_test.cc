#include "sqlite3_client/request_processor.h"

#include <drogon/HttpRequest.h>    // for HttpRequestPtr
#include <drogon/HttpResponse.h>   // for HttpResponse
#include <drogon/drogon_test.h>    // for Case (ptr only), DROGON_TEST,
#include <drogon/orm/Exception.h>  // for DrogonDbException #include
#include <json/value.h>            // for Value

#include <iostream>

#include "sqlite3_client/helpers.h"
#include "test_utilities/include/random_string_generator.h"

const int kUsernameLen = 20;
const int kPasswordLen = 30;
const int kMasterPasswordLen = 30;

DROGON_TEST(RequestProcessorTests_ParseRequestJson_ExceptionTest) {
  // Testing
  // 1. ParseRequest function should not throw even if json is null
  Json::Value request;
  auto http_request = drogon::HttpRequest::newHttpJsonRequest(request);
  auto http_response = drogon::HttpResponse::newHttpJsonResponse(request);
  Json::Value response_object;

  MANDATE_NOTHROW(minpass::sqlite3_client::RequestProcessor::ParseRequestJson(
      http_request, http_response, response_object));
}

DROGON_TEST(RequestProcessorTests_ParseRequestJson_ReturnValueTest1) {
  // Testing
  // 1. ParseRequest must return the correct structure bindings when json
  // was parsed

  Json::Value request;
  request["email"] = "mail@mail.com";
  request["password"] = minpass::tests::generate_random_string(kUsernameLen);
  request["username"] = minpass::tests::generate_random_string(kPasswordLen);
  request["master_password"] =
      minpass::tests::generate_random_string(kMasterPasswordLen);

  // build the json into a string
  Json::StreamWriterBuilder builder;
  builder["indentation"] = "";  // If you want whitespace-less output
  const std::string output = Json::writeString(builder, request);

  auto http_request = drogon::HttpRequest::newHttpRequest();
  http_request->setBody(output);  // feed in that string
  http_request->setContentTypeCode(
      drogon::CT_APPLICATION_JSON);  // feed in that string

  auto http_response = drogon::HttpResponse::newHttpResponse();
  Json::Value response_object;

  auto [is_valid, email, username, password, master_password] =
      minpass::sqlite3_client::RequestProcessor::ParseRequestJson(
          http_request, http_response, response_object);

  CHECK(is_valid == true);
  CHECK(email.get() == request["email"]);
  CHECK(username.get() == request["username"]);
  CHECK(password.get() == request["password"]);
  CHECK(master_password.get() == request["master_password"]);
  CHECK(http_response->statusCode() == drogon::k202Accepted);
}

DROGON_TEST(RequestProcessorTests_ParseRequestJson_ReturnValueTest2) {
  // Testing
  // 1. ParseRequest must return empty structure bindings when json
  // was not parsed

  std::string illegal_request;
  auto http_request = drogon::HttpRequest::newHttpRequest();
  http_request->setBody(illegal_request);
  http_request->setContentTypeCode(drogon::CT_APPLICATION_JSON);
  auto http_response = drogon::HttpResponse::newHttpResponse();
  Json::Value response_object;

  auto [is_valid, email, username, password, master_password] =
      minpass::sqlite3_client::RequestProcessor::ParseRequestJson(
          http_request, http_response, response_object);

  CHECK(is_valid == false);
  CHECK(email.get() == "");
  CHECK(username.get() == "");
  CHECK(password.get() == "");
  CHECK(master_password.get() == "");
  CHECK(http_response->statusCode() == drogon::k400BadRequest);
}

DROGON_TEST(RequestProcessorTests_ParseRequestJson_MasterPasswordNotGiven) {
  // Testing
  // 1. ParseRequest must return error response when master_password is not in
  // the request

  Json::Value request;
  request["email"] = "mail@mail.com";
  request["password"] = minpass::tests::generate_random_string(kUsernameLen);
  request["username"] = minpass::tests::generate_random_string(kPasswordLen);

  // build the json into a string
  Json::StreamWriterBuilder builder;
  builder["indentation"] = "";  // If you want whitespace-less output
  const std::string output = Json::writeString(builder, request);

  auto http_request = drogon::HttpRequest::newHttpRequest();
  http_request->setBody(output);  // feed in that string
  http_request->setContentTypeCode(
      drogon::CT_APPLICATION_JSON);  // feed in that string

  auto http_response = drogon::HttpResponse::newHttpResponse();
  Json::Value response_object;

  auto [is_valid, email, username, password, master_password] =
      minpass::sqlite3_client::RequestProcessor::ParseRequestJson(
          http_request, http_response, response_object);

  CHECK(is_valid == false);
  CHECK(email.get() == "");
  CHECK(username.get() == "");
  CHECK(password.get() == "");
  CHECK(master_password.get() == "");
  CHECK(http_response->statusCode() == drogon::k400BadRequest);
}

DROGON_TEST(RequestProcessorTests_ParseRequestJson_SQLi) {
  // Testing
  // 1. ParseRequest must not break again SQL injections

  Json::Value sql_injection;
  sql_injection["email"] = "mail@mail.com";
  sql_injection["username"] =
      minpass::tests::generate_random_string(kUsernameLen).data();
  sql_injection["password"] = "pas22sls'); AND '1' = '1'";
  sql_injection["master_password"] =
      minpass::tests::generate_random_string(kMasterPasswordLen).data();

  // build the json into a string
  Json::StreamWriterBuilder builder;
  builder["indentation"] = "";  // If you want whitespace-less output
  const std::string output = Json::writeString(builder, sql_injection);

  auto http_request = drogon::HttpRequest::newHttpRequest();
  http_request->setBody(output);  // feed in that string
  http_request->setContentTypeCode(
      drogon::CT_APPLICATION_JSON);  // feed in that string
  auto http_response = drogon::HttpResponse::newHttpResponse();
  Json::Value response_object;

  auto [is_valid, email, username, password, master_password] =
      minpass::sqlite3_client::RequestProcessor::ParseRequestJson(
          http_request, http_response, response_object);

  CHECK(is_valid == true);
  CHECK(email.get() == sql_injection["email"]);
  CHECK(username.get() == sql_injection["username"]);
  CHECK(password.get() == sql_injection["password"]);
  CHECK(master_password.get() == sql_injection["master_password"]);
  CHECK(http_response->statusCode() == drogon::k202Accepted);
}

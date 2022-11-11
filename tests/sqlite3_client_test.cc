#include "sqlite3_client.h"

#include <drogon/HttpClient.h>   // for HttpClient
#include <drogon/HttpRequest.h>  // for HttpRequest
#include <drogon/drogon_test.h>  // for CHECK, Case (ptr only), REQ...
#include <json/config.h>         // for JSONCPP_STRING
#include <json/reader.h>         // for CharReader, CharReaderBuilder
#include <json/value.h>          // for Value
#include <json/writer.h>         // for operator<<

#include <string_view>  // for basic_string_view

#include "test_utilities/include/random_string_generator.h"

#define PORT "8080"  // if you have a different port to listen
#define PATH "/minpass/SQLite3Client/"

const int kUsernameLen = 20;
const int kEmailLen = 20;
const int kPasswordLen = 30;

DROGON_TEST(RestAPITest_Get_Case1) {
  // Testing
  // Get when the website is not in database.

  auto client = drogon::HttpClient::newHttpClient("http://localhost:" PORT);
  Json::Value json;
  auto request = drogon::HttpRequest::newCustomHttpRequest(json);
  request->setMethod(drogon::HttpMethod::Get);
  request->setPath(PATH "website=notthere.com");
  client->sendRequest(request, [TEST_CTX](
                                   drogon::ReqResult result,
                                   const drogon::HttpResponsePtr& response) {
    REQUIRE(result == drogon::ReqResult::Ok);
    REQUIRE(response != nullptr);

    auto response_json = *(response->getJsonObject());

    CHECK(response_json["message"] == "website not found");
    CHECK(response->getStatusCode() == drogon::HttpStatusCode::k404NotFound);
    CHECK(response->contentType() == drogon::CT_APPLICATION_JSON);
  });
}

DROGON_TEST(RestAPITest_Get_Case2) {
  // Testing
  // Get when the website is in database.

  auto client = drogon::HttpClient::newHttpClient("http://localhost:" PORT);

  Json::Value json;
  json["email"] = minpass::tests::generate_random_string(kEmailLen);
  json["username"] = minpass::tests::generate_random_string(kUsernameLen);
  json["password"] = minpass::tests::generate_random_string(kPasswordLen);

  auto request_post = drogon::HttpRequest::newHttpJsonRequest(json);
  request_post->setMethod(drogon::HttpMethod::Post);
  request_post->setPath(PATH "website=google.com");

  client->sendRequest(
      request_post, [TEST_CTX](drogon::ReqResult result,
                               const drogon::HttpResponsePtr& response) {
        REQUIRE(result == drogon::ReqResult::Ok);
        REQUIRE(response != nullptr);

        auto response_json = *(response->getJsonObject());

        CHECK(response_json["message"] == "ok");
        CHECK(response->getStatusCode() ==
              drogon::HttpStatusCode::k202Accepted);
        CHECK(response->contentType() == drogon::CT_APPLICATION_JSON);
      });

  auto request_get = drogon::HttpRequest::newHttpRequest();
  request_get->setMethod(drogon::HttpMethod::Get);
  request_get->setPath(PATH "website=google.com");
  client->sendRequest(
      request_get, [TEST_CTX](drogon::ReqResult result,
                              const drogon::HttpResponsePtr& response) {
        REQUIRE(result == drogon::ReqResult::Ok);
        REQUIRE(response != nullptr);

        auto response_json = *(response->getJsonObject());

        CHECK(response_json["message"] == "ok");
        CHECK(response->getStatusCode() == drogon::HttpStatusCode::k200OK);
        CHECK(response->contentType() == drogon::CT_APPLICATION_JSON);
      });
}

DROGON_TEST(RestAPITest_Delete_Case1) {
  // Testing
  // Delete when the website is in database

  auto client = drogon::HttpClient::newHttpClient("http://localhost:" PORT);

  Json::Value json;
  json["email"] = minpass::tests::generate_random_string(kEmailLen);
  json["username"] = minpass::tests::generate_random_string(kUsernameLen);
  json["password"] = minpass::tests::generate_random_string(kPasswordLen);

  auto request_post = drogon::HttpRequest::newHttpJsonRequest(json);
  request_post->setMethod(drogon::HttpMethod::Post);
  request_post->setPath(PATH "website=google.com");

  client->sendRequest(
      request_post, [TEST_CTX](drogon::ReqResult result,
                               const drogon::HttpResponsePtr& response) {
        REQUIRE(result == drogon::ReqResult::Ok);
        REQUIRE(response != nullptr);

        auto response_json = *(response->getJsonObject());

        CHECK(response_json["message"] == "ok");
        CHECK(response->getStatusCode() ==
              drogon::HttpStatusCode::k202Accepted);
        CHECK(response->contentType() == drogon::CT_APPLICATION_JSON);
      });

  auto request_delete = drogon::HttpRequest::newHttpRequest();
  request_delete->setMethod(drogon::HttpMethod::Delete);
  request_delete->setPath(PATH "website=google.com");
  client->sendRequest(
      request_delete, [TEST_CTX](drogon::ReqResult result,
                                 const drogon::HttpResponsePtr& response) {
        REQUIRE(result == drogon::ReqResult::Ok);
        REQUIRE(response != nullptr);

        auto response_json = *(response->getJsonObject());

        CHECK(response_json["message"] == "ok");
        CHECK(response->getStatusCode() == drogon::HttpStatusCode::k200OK);
        CHECK(response->contentType() == drogon::CT_APPLICATION_JSON);
      });
}

// Need more tests to validate requests

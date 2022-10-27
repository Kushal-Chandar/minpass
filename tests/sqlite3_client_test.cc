#include "sqlite3_client.h"

#include <__memory/shared_ptr.h>          // for shared_ptr
#include <__memory/unique_ptr.h>          // for unique_ptr
#include <__type_traits/remove_extent.h>  // for remove_extent_t
#include <drogon/HttpClient.h>            // for HttpClient
#include <drogon/HttpRequest.h>           // for HttpRequest
#include <drogon/drogon_test.h>           // for CHECK, Case (ptr only), REQ...
#include <json/config.h>                  // for JSONCPP_STRING
#include <json/reader.h>                  // for CharReader, CharReaderBuilder
#include <json/value.h>                   // for Value
#include <json/writer.h>                  // for operator<<

#include <string_view>  // for basic_string_view

namespace drogon {
class DrObjectBase;
}  // namespace drogon

#define PORT "8080"  // if you have a different port to listen
#define PATH "/minpass/SQLite3Client/"

DROGON_TEST(RestAPITest_Get_Case1) {
  // Testing
  // Get when the website is not in database.

  auto client = drogon::HttpClient::newHttpClient("http://localhost:" PORT);
  Json::Value json;
  // json["email"] = "a@b.com";
  // json["username"] = "asd";
  // json["password"] = "skdfis83nd8c9en";
  auto request = drogon::HttpRequest::newCustomHttpRequest(json);
  request->setMethod(drogon::HttpMethod::Get);
  request->setPath(PATH "website=notthere.com");
  client->sendRequest(request, [TEST_CTX](
                                   drogon::ReqResult result,
                                   const drogon::HttpResponsePtr& response) {
    REQUIRE(result == drogon::ReqResult::Ok);
    REQUIRE(response != nullptr);

    auto raw_response_json = response->body();
    JSONCPP_STRING err;
    Json::Value response_json;
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    reader->parse(raw_response_json.data(),
                  raw_response_json.data() + raw_response_json.size(),
                  &response_json, &err);

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
  auto request = drogon::HttpRequest::newCustomHttpRequest(json);
  request->setMethod(drogon::HttpMethod::Get);
  request->setPath(PATH "website=google.com");
  client->sendRequest(
      request, [TEST_CTX](drogon::ReqResult result,
                          const drogon::HttpResponsePtr& response) {
        REQUIRE(result == drogon::ReqResult::Ok);
        REQUIRE(response != nullptr);
        auto raw_response_json = response->body();
        JSONCPP_STRING err;
        Json::Value response_json;
        Json::CharReaderBuilder builder;
        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        reader->parse(raw_response_json.data(),
                      raw_response_json.data() + raw_response_json.size(),
                      &response_json, &err);
        CHECK(response_json["message"] == "ok");
        CHECK(response->getStatusCode() == drogon::HttpStatusCode::k200OK);
        CHECK(response->contentType() == drogon::CT_APPLICATION_JSON);
      });
}

// Need more tests
// to validate requests

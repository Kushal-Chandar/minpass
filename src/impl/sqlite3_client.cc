#include "sqlite3_client.h"

#include <drogon/HttpAppFramework.h>  // for app, HttpAppFramework
#include <json/value.h>               // for Value

#include <tuple>  // for tuple_element<>::type

#include "sqlite3_client/helpers.h"         // for Helpers
#include "sqlite3_client/json_processor.h"  // for JsonProcessor
namespace drogon {
class DrObjectBase;
}  // namespace drogon

namespace minpass {

SQLite3Client::SQLite3Client(const DatabaseName &database_name,
                             TableName table_name)
    : client_(drogon::app().getDbClient(database_name.get())),
      table_name_(std::move(table_name)) {
  client_->execSqlAsync("CREATE TABLE IF NOT EXISTS " + table_name_.get() +
                            " ("
                            "  Website varchar(100) NOT NULL PRIMARY KEY,"
                            "  Email varchar(50),"
                            "  Username varchar(100),"
                            "  Password varchar(50) NOT NULL"
                            ");",
                        sqlite3_client::Helpers::EmptyCallback,
                        sqlite3_client::Helpers::CommonExceptionCatch);
}

auto SQLite3Client::SetPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    const Website &website) -> void {
  Json::Value response_object;
  drogon::HttpResponsePtr http_response;
  auto request_data = sqlite3_client::JsonProcessor::ParseRequestJson(
      http_request, http_response, response_object);
  if (request_data) {
    auto password_data = request_data.value();
    sqlite3_client::JsonProcessor::EncryptData(password_data);
    client_->execSqlAsync(
        "INSERT INTO " + table_name_.get() + " VALUES ($1, $2, $3, $4);",
        sqlite3_client::Helpers::EmptyCallback,
        sqlite3_client::Helpers::CommonExceptionCatch, website.get(),
        password_data.email.get(), password_data.username.get(),
        password_data.password.get());
  }
  http_callback(http_response);
}

auto SQLite3Client::GetPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    const Website &website) -> void {
  client_->execSqlAsync(
      "SELECT * FROM " + table_name_.get() + " WHERE Website = $1;",
      [http_request, http_callback](const drogon::orm::Result &result) {
        Json::Value response_object;
        drogon::HttpResponsePtr http_response;
        auto request_data = sqlite3_client::JsonProcessor::ParseRequestJson(
            http_request, http_response, response_object);
        if (request_data) {
          auto password_data = request_data.value();
          drogon::HttpStatusCode status_code = drogon::k404NotFound;
          response_object["message"] = "website not found";
          if (!result.empty()) {
            auto first_row = result[0];
            status_code = drogon::k200OK;
            response_object["message"] = "ok";
            response_object["website"] = first_row["website"].as<std::string>();

            password_data.email = Email(first_row["email"].as<std::string>());
            password_data.username =
                Username(first_row["username"].as<std::string>());
            password_data.password =
                Password(first_row["password"].as<std::string>());

            sqlite3_client::JsonProcessor::DecryptData(password_data);

            response_object["email"] = password_data.email.get();
            response_object["username"] = password_data.username.get();
            response_object["password"] = password_data.password.get();
          }
          http_callback(sqlite3_client::Helpers::MakeResponse(response_object,
                                                              status_code));
        } else {
          http_callback(http_response);
        }
      },
      sqlite3_client::Helpers::CommonExceptionCatch, website.get());
}

auto SQLite3Client::ModifyPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    const Website &website) -> void {
  Json::Value response_object;
  drogon::HttpResponsePtr http_response;

  // Todo: update passwords should only update the data given in json object
  // steps: do a async get call, to get email, username, password
  // now parse the request
  // check for items that don't match, and update them with the items in request

  auto request_data = sqlite3_client::JsonProcessor::ParseRequestJson(
      http_request, http_response, response_object);
  if (request_data) {
    auto password_data = request_data.value();
    sqlite3_client::JsonProcessor::EncryptData(password_data);
    client_->execSqlAsync("UPDATE " + table_name_.get() +
                              " SET Email = $1, Username = $2, Password = $3"
                              " WHERE Website = $4;",
                          sqlite3_client::Helpers::EmptyCallback,
                          sqlite3_client::Helpers::CommonExceptionCatch,
                          password_data.email.get(),
                          password_data.username.get(),
                          password_data.password.get(), website.get());
  }
  http_callback(http_response);
}

auto SQLite3Client::RemovePasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    const Website &website) -> void {
  Json::Value response_object;
  client_->execSqlAsync(
      "DELETE FROM " + table_name_.get() + " WHERE Website = $1;",
      sqlite3_client::Helpers::EmptyCallback,
      sqlite3_client::Helpers::CommonExceptionCatch, website.get());
  response_object["message"] = "ok";
  http_callback(sqlite3_client::Helpers::MakeResponse(response_object));
}

auto SQLite3Client::QuitServer(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback)
    -> void {
  Json::Value response_object;
  response_object["message"] = "server has been stopped";
  http_callback(sqlite3_client::Helpers::MakeResponse(
      response_object, drogon::k503ServiceUnavailable));
  drogon::app().quit();
}

}  // namespace minpass

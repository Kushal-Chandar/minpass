#include "sqlite3_client.h"

#include <drogon/HttpAppFramework.h>  // for app, HttpAppFramework
#include <json/value.h>               // for Value

#include <tuple>  // for tuple_element<>::type

#include "sqlite3_client/helpers.h"          // for Helpers
#include "sqlite3_client/request_handler.h"  // for Request Handler
namespace drogon {
class DrObjectBase;
}  // namespace drogon

namespace minpass {

SQLite3Client::SQLite3Client(const DatabaseName &database_name,
                             TableName table_name)
    : client_(drogon::app().getDbClient(database_name.get())),
      table_name_(std::move(table_name)) {
  client_->execSqlAsync("CREATE TABLE IF NOT EXISTS " + table_name_.get() +
                            " (\n"
                            "  Website varchar(100) NOT NULL PRIMARY KEY,\n"
                            "  Email varchar(50),\n"
                            "  Username varchar(100),\n"
                            "  Password varchar(50) NOT NULL\n"
                            ");\n",
                        sqlite3_client::Helpers::EmptyCallback,
                        sqlite3_client::Helpers::CommonExceptionCatch);
}

auto SQLite3Client::SetPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    const Website &website) -> void {
  Json::Value response_object;
  drogon::HttpResponsePtr http_response;
  auto [is_valid, email, username, password] =
      sqlite3_client::RequestHandler::ParseRequestJson(
          http_request, http_response, response_object);
  if (is_valid) {
    client_->execSqlAsync(
        "INSERT INTO " + table_name_.get() + " VALUES ($1, $2, $3, $4);\n",
        sqlite3_client::Helpers::EmptyCallback,
        sqlite3_client::Helpers::CommonExceptionCatch, website.get(),
        email.get(), username.get(), password.get());
  }
  http_callback(http_response);
}

auto SQLite3Client::GetPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    const Website &website) -> void {
  client_->execSqlAsync(
      "SELECT * FROM " + table_name_.get() + " WHERE Website = $1;\n",
      [http_callback]([[maybe_unused]] const drogon::orm::Result &result) {
        Json::Value response_object;
        drogon::HttpStatusCode status_code = drogon::k404NotFound;
        response_object["message"] = "website not found";
        if (!result.empty()) {
          auto first_row = result[0];
          status_code = drogon::k200OK;
          response_object["message"] = "ok";
          response_object["website"] = first_row["website"].as<std::string>();
          response_object["email"] = first_row["email"].as<std::string>();
          response_object["username"] = first_row["username"].as<std::string>();
          response_object["password"] = first_row["password"].as<std::string>();
        }
        http_callback(sqlite3_client::Helpers::MakeResponse(response_object,
                                                            status_code));
      },
      sqlite3_client::Helpers::CommonExceptionCatch, website.get());
}

auto SQLite3Client::ModifyPasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    const Website &website) -> void {
  Json::Value response_object;
  drogon::HttpResponsePtr http_response;
  auto [is_valid, email, username, password] =
      sqlite3_client::RequestHandler::ParseRequestJson(
          http_request, http_response, response_object);
  if (is_valid) {
    client_->execSqlAsync("UPDATE " + table_name_.get() +
                              " SET Email = $1, Username = $2, Password = $3\n"
                              "WHERE Website = $4;\n",
                          sqlite3_client::Helpers::EmptyCallback,
                          sqlite3_client::Helpers::CommonExceptionCatch,
                          email.get(), username.get(), password.get(),
                          website.get());
  }
  http_callback(http_response);
}

auto SQLite3Client::RemovePasswordData(
    [[maybe_unused]] const drogon::HttpRequestPtr &http_request,
    std::function<void(const drogon::HttpResponsePtr &)> &&http_callback,
    const Website &website) -> void {
  Json::Value response_object;
  client_->execSqlAsync(
      "DELETE FROM " + table_name_.get() + " WHERE Website = $1;\n",
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

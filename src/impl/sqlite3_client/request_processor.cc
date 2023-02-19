#include <drogon/drogon_callbacks.h>  // for HttpResponsePtr, HttpRequestPtr
#include <sqlite3_client/helpers.h>
#include <sqlite3_client/json_processor.h>
#include <sqlite3_client/request_processor.h>

namespace minpass::sqlite3_client {

auto RequestProcessor::getHttpResponsePtr() -> drogon::HttpResponsePtr {
  return http_response_;
}

auto RequestProcessor::SetPassword() -> void {
  if (request_data) {
    auto [email, username, password, master_password] = request_data.value();
    sqlite3_client::JsonProcessor::EncryptData(email, username, password,
                                               master_password);
    client_->execSqlAsync(
        "INSERT INTO " + table_name_.get() + " VALUES ($1, $2, $3, $4);",
        sqlite3_client::Helpers::EmptyCallback,
        sqlite3_client::Helpers::CommonExceptionCatch, website.get(),
        sqlite3_client::Helpers::MakeResponse(), email.get(), username.get(),
        password.get());
  }
}

auto RequestProcessor::GetPassword() -> void {
  auto request_data = sqlite3_client::JsonProcessor::ParseRequestJson(
      http_request, http_response_, response_object_);
  if (request_data) {
    auto [email, username, password, master_password] = request_data.value();
    client_->this->execSqlAsync();
    sqlite3_client = e
  }
}
auto RequestProcessor::UpdatePassword() -> void {}
auto RequestProcessor::RemovePassword() -> void {}

}  // namespace minpass::sqlite3_client

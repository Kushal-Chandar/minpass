#include "database_abstraction.h"

#include <drogon/drogon.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/printf.h>

#include "minpass_types.h"

namespace minpass {

DatabaseAbstraction::DatabaseAbstraction(const std::string& database_name,
                                         std::string_view table_name)
    : table_name_(table_name) {
  client_ = drogon::app().getDbClient(database_name);
  CreateTable();
}

auto DatabaseAbstraction::CreateTable() -> void {
  auto sql_query = CreateTableQuery();
  auto call_back = []([[maybe_unused]] bool isNull) {};
  *client_ << sql_query >> call_back >>
      [](const drogon::orm::DrogonDbException& error) {
        fmt::print(fmt::fg(fmt::color::red), "error: {}\n",
                   error.base().what());
      };
}

auto DatabaseAbstraction::InsertPassword(Website& website, Email& email,
                                         Username& username, Password& password)
    -> std::shared_ptr<Json::Value> {
  auto response = std::make_shared<Json::Value>();
  auto sql_query = InsertPasswordQuery(website, email, username, password);
  auto call_back = [response]([[maybe_unused]] bool isNull) {
    (*response)["result"] = "ok";
  };
  auto exception = [response](const drogon::orm::DrogonDbException& error) {
    fmt::print(fmt::fg(fmt::color::red), "error: {}\n", error.base().what());
    (*response)["result"] = error.base().what();
  };
  fmt::print("{}", response->asString());
  *client_ << sql_query >> call_back >> exception;
  return response;
}

auto DatabaseAbstraction::RetrievePassword(Website& website)
    -> std::shared_ptr<Json::Value> {
  auto sql_query = RetrievePasswordQuery(website);
  auto response = std::make_shared<Json::Value>();
  auto async_counter = std::make_shared<int>();
  auto call_back = [async_counter, response](bool isNull, Website website,
                                             Email email, Username username,
                                             Password password) {
    if (!isNull) {
      (*response)["username"] = username.get();
      (*response)["email"] = email.get();
      (*response)["password"] = password.get();
      (*response)["result"] = "ok";
      fmt::print("{}--", response->isNull());

    } else {
      (*response)["website"] = website.get();
      (*response)["count"] = '0';
      (*response)["result"] = "website not found";
    }
  };
  auto exception = [response](const drogon::orm::DrogonDbException& error) {
    fmt::print(fmt::fg(fmt::color::red), "error: {}\n", error.base().what());
    (*response)["result"] = error.base().what();
  };
  *client_ << sql_query >> call_back >> exception;
  fmt::print("{}--", response->asString());
  return response;
}

auto DatabaseAbstraction::DeletePassword(Website& website)
    -> std::shared_ptr<Json::Value> {
  auto response = std::make_shared<Json::Value>();
  auto sql_query = DeletePasswordQuery(website);
  auto call_back = [response]([[maybe_unused]] bool isNull) {
    (*response)["result"] = "ok";
  };
  auto exception = [response](const drogon::orm::DrogonDbException& error) {
    fmt::print(fmt::fg(fmt::color::red), "error: {}\n", error.base().what());
    (*response)["result"] = error.base().what();
  };
  *client_ << sql_query >> call_back >> exception;
  return response;
}

auto DatabaseAbstraction::CreateTableQuery() -> std::string {
  auto sql_query = fmt::format(
      "CREATE TABLE IF NOT EXISTS {} (\n"
      "  Website varchar(100) NOT NULL PRIMARY KEY,\n"
      "  Email varchar(50),\n"
      "  UserName varchar(100),\n"
      "  Password varchar(50) NOT NULL\n"
      ");\n",
      table_name_);
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return sql_query;
}

auto DatabaseAbstraction::InsertPasswordQuery(Website& website, Email& email,
                                              Username& username,
                                              Password& password)
    -> std::string {
  auto sql_query = fmt::format(
      "INSERT INTO {}\n"
      "VALUES ('{}', '{}', '{}', '{}');\n",
      table_name_, website.get(), email.get(), username.get(), password.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return sql_query;
}

auto DatabaseAbstraction::RetrievePasswordQuery(Website& website)
    -> std::string {
  auto sql_query = fmt::format(
      "SELECT * FROM {}\n"
      "WHERE Website = '{}';\n",
      table_name_, website.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return sql_query;
}

auto DatabaseAbstraction::DeletePasswordQuery(Website& website) -> std::string {
  auto sql_query = fmt::format(
      "DELETE FROM {}\n"
      "WHERE Website = '{}';\n",
      table_name_, website.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return sql_query;
}

}  // namespace minpass

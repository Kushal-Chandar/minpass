#include "database_abstraction.h"

#include <drogon/drogon.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/printf.h>

#include "minpass_types.h"

namespace minpass {

DatabaseAbstraction::DatabaseAbstraction(std::string_view database_name,
                                         std::string_view table_name)
    : table_name_(table_name) {
  client_ = drogon::app().getDbClient(database_name.data());
  CreateTable();
}

auto DatabaseAbstraction::CreateTable() -> void {
  auto client = drogon::app().getDbClient("minpass");
  auto sql_query = fmt::format(
      "CREATE TABLE IF NOT EXISTS {} (\n"
      "  Website varchar(100) NOT NULL PRIMARY KEY,\n"
      "  Email varchar(50),\n"
      "  UserName varchar(100),\n"
      "  Password varchar(50) NOT NULL\n"
      ");\n",
      table_name_);
  LOG_TRACE << sql_query << '\n';
  auto call_back = [](bool isNull) {
    if (!isNull) {
      fmt::print("{}\n", isNull);
    }
  };
  *client << sql_query >> call_back >>
      [](const drogon::orm::DrogonDbException& error) {
        fmt::print(fmt::fg(fmt::color::red), "error: {}\n",
                   error.base().what());
      };
  fmt::print("Table Created\n");
}

auto DatabaseAbstraction::InsertPassword(Website& website, Email& email,
                                         Username& username, Password& password)
    -> std::shared_ptr<Json::Value> {
  auto client = drogon::app().getDbClient("minpass");
  auto sql_query = fmt::format(
      "INSERT INTO {}\n"
      "VALUES ('{}', '{}', '{}', '{}');\n",
      table_name_, website.get(), email.get(), username.get(), password.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);

  auto call_back = [](bool isNull) {
    if (!isNull) {
      fmt::print("{}\n", isNull);
    }
  };
  *client << sql_query >> call_back >>
      [](const drogon::orm::DrogonDbException& error) {
        fmt::print(fmt::fg(fmt::color::red), "error: {}\n",
                   error.base().what());
      };
  fmt::print("Value Inserted\n");
}

auto DatabaseAbstraction::RetrievePassword(Website& website)
    -> std::shared_ptr<Json::Value> {
  auto client = drogon::app().getDbClient("minpass");
  auto sql_query = fmt::format(
      "SELECT * FROM {}\n"
      "WHERE Website = '{}';\n",
      table_name_, website.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  auto response_ptr = std::make_shared<Json::Value>();
  auto async_counter = std::make_shared<int>();
  auto call_back = [async_counter, response_ptr](bool isNull, Website website,
                                                 Email email, Username username,
                                                 Password password) {
    if (!isNull) {
      fmt::print("{}-{}-{}-{}-{}\n", (*async_counter)++, website.get(),
                 email.get(), username.get(), password.get());
      (*response_ptr)["username"] = username.get();
      (*response_ptr)["email"] = email.get();
      (*response_ptr)["password"] = password.get();

    } else {
      fmt::print("{}\n", (*async_counter));
      (*response_ptr)["count"] = 0;
    }
  };
  fmt::print("hello\n");
  *client << sql_query >> call_back >>
      [](const drogon::orm::DrogonDbException& error) {
        fmt::print(fmt::fg(fmt::color::red), "error: {}\n",
                   error.base().what());
      };
  fmt::print("Value Retrieved\n");
  return response_ptr;
}

auto DatabaseAbstraction::DeletePassword(Website& website)
    -> std::shared_ptr<Json::Value> {
  auto client = drogon::app().getDbClient("minpass");
  // Json::Value response;
  auto sql_query = fmt::format(
      "DELETE FROM {}\n"
      "WHERE Website = '{}';\n",
      table_name_, website.get());

  auto call_back = [](bool isNull) {
    if (!isNull) {
      fmt::print("{}\n", isNull);
    }
  };

  *client << sql_query >> call_back >>
      [](const drogon::orm::DrogonDbException& error) {
        fmt::print(fmt::fg(fmt::color::red), "error: {}\n",
                   error.base().what());
      };
  fmt::print("Value Retrieved\n");
  // return response;
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
  return std::move(sql_query);
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
  return std::move(sql_query);
}

auto DatabaseAbstraction::RetrievePasswordQuery(Website& website)
    -> std::string {
  auto sql_query = fmt::format(
      "SELECT * FROM {}\n"
      "WHERE Website = '{}';\n",
      table_name_, website.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return std::move(sql_query);
}

auto DatabaseAbstraction::DeletePasswordQuery(Website& website) -> std::string {
  auto sql_query = fmt::format(
      "DELETE FROM {}\n"
      "WHERE Website = '{}';\n",
      table_name_, website.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return std::move(sql_query);
}

}  // namespace minpass

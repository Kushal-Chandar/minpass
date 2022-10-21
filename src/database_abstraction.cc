#include "database_abstraction.h"

#include <drogon/drogon.h>
#include <fmt/color.h>
#include <fmt/core.h>
#include <fmt/printf.h>

#include "minpass_types.h"

namespace minpass {

DatabaseAbstraction::DatabaseAbstraction(std::string_view table_name)
    : table_name_(table_name) {
  CreateTable();
}

auto DatabaseAbstraction::CreateTable() -> void {
  auto client = drogon::app().getDbClient();
  auto sql_query = fmt::format(
      "CREATE TABLE {} ("
      "  Website varchar(100) NOT NULL PRIMARY KEY,"
      "  Email varchar(50),"
      "  UserName varchar(100),"
      "  Password varchar(50) NOT NULL,"
      ");",
      table_name_);
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
    -> void {
  auto client = drogon::app().getDbClient();
  auto sql_query = fmt::format(
      "INSERT INTO {}"
      "VALUES({}, {}, {}, {});",
      table_name_, website.get(), email.get(), username.get(), password.get());
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

auto DatabaseAbstraction::RetrievePassword(Website& website) -> Json::Value {
  auto client = drogon::app().getDbClient();
  Json::Value response;
  auto sql_query = fmt::format(
      "SELECT * FROM {}"
      "WHERE Website = '{}'",
      table_name_, website.get());

  auto async_counter = std::make_unique<int>(0);
  auto call_back = [&async_counter, &response](bool isNull, Email email,
                                               Username username,
                                               Password password) {
    if (!isNull) {
      fmt::print("{}\t{}\t{}\t{}\n", (*async_counter)++, email.get(),
                 username.get(), password.get());
      response["username"] = username.get();
      response["email"] = email.get();
      response["password"] = password.get();

    } else {
      fmt::print("{}\n", *async_counter);
    }
  };
  *client << sql_query >> call_back >>
      [](const drogon::orm::DrogonDbException& error) {
        fmt::print(fmt::fg(fmt::color::red), "error: {}\n",
                   error.base().what());
      };
  fmt::print("Value Retrieved\n");
  return response;
}

}  // namespace minpass

#include "sqlite3_queries.h"

#include <fmt/color.h>   // for fg, print, color, color::green
#include <fmt/core.h>    // for basic_string_view, format
#include <fmt/format.h>  // for buffer::append

#include "minpass_types.h"  // for Website, Email, Password, Username

namespace minpass {

SQLite3Queries::SQLite3Queries(std::string_view table_name)
    : table_name_(table_name) {}

auto SQLite3Queries::CreateTableQuery() -> std::string {
  auto sql_query = fmt::format(
      "CREATE TABLE IF NOT EXISTS {} (\n"
      "  Website varchar(100) NOT NULL PRIMARY KEY,\n"
      "  Email varchar(50),\n"
      "  Username varchar(100),\n"
      "  Password varchar(50) NOT NULL\n"
      ");\n",
      table_name_);
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return sql_query;
}

auto SQLite3Queries::CreatePasswordQuery(Website& website, Email& email,
                                         Username& username, Password& password)
    -> std::string {
  auto sql_query = fmt::format(
      "INSERT INTO {}\n"
      "VALUES ('{}', '{}', '{}', '{}');\n",
      table_name_, website.get(), email.get(), username.get(), password.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return sql_query;
}

auto SQLite3Queries::ReadPasswordQuery(Website& website) -> std::string {
  auto sql_query = fmt::format(
      "SELECT * FROM {}\n"
      "WHERE Website = '{}';\n",
      table_name_, website.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return sql_query;
}

auto SQLite3Queries::UpdatePasswordQuery(Website& website, Email& email,
                                         Username& username, Password& password)
    -> std::string {
  auto sql_query = fmt::format(
      "UPDATE {}\n"
      "SET Email = '{}', Username = '{}', Password = '{}'\n"
      "WHERE Website = '{}';\n",
      table_name_, email.get(), username.get(), password.get(), website.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return sql_query;
}

auto SQLite3Queries::DeletePasswordQuery(Website& website) -> std::string {
  auto sql_query = fmt::format(
      "DELETE FROM {}\n"
      "WHERE Website = '{}';\n",
      table_name_, website.get());
  fmt::print(fmt::fg(fmt::color::green), "{}\n", sql_query);
  return sql_query;
}

}  // namespace minpass

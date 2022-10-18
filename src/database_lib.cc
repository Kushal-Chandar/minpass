#include "database_lib.h"

#include <fmt\core.h>
#include <fmt\printf.h>
#include <sqlite3.h>

#include <exception>
#include <vector>

minpass::MinpassDataBase::MinpassDataBase() {
  int error_code = sqlite3_open("minpass.db", &database_);
  CreateTable();
  HandleError(error_code);
}

minpass::MinpassDataBase::MinpassDataBase(std::string_view& database_name) {
  int error_code = sqlite3_open(database_name.data(), &database_);
  HandleError(error_code);
  CreateTable();
}

minpass::MinpassDataBase::~MinpassDataBase() {
  int error_code = sqlite3_close(database_);
  HandleError(error_code);
}

auto minpass::MinpassDataBase::set_password(const Website& site,
                                            const Username& username,
                                            const Email& email,
                                            const Password& password) -> void {
  auto sql_query = fmt::format(
      "INSERT INTO MINPASS"
      "VALUES({}, {}, {}, {});",
      site.value_, username.value_, email.value_, password.value_);
  int error_code =
      sqlite3_exec(database_, sql_query.data(), nullptr, nullptr, nullptr);
  HandleError(error_code);
}

auto minpass::MinpassDataBase::get_password(const Website& site)
    -> std::vector<std::string_view> {
  std::vector<std::string_view> password;
  sqlite3_stmt* stmt = nullptr;
  auto sql_query = fmt::format(
      "SELECT * FROM MINPASS"
      "WHERE SITE='{}';",
      site.value_);

  int error_code =
      sqlite3_prepare_v2(database_, sql_query.data(), -1, &stmt, nullptr);
  HandleError(error_code);

  while ((error_code = sqlite3_step(stmt)) == SQLITE_LIMIT_COLUMN) {
    sqlite3_column_int(stmt, 0);
    const unsigned char* name = sqlite3_column_text(stmt, 1);
    // ...
  }

  if (error_code != SQLITE_DONE) {
    fmt::print("{}\n", sqlite3_errmsg(database_));
  }
  sqlite3_finalize(stmt);
  return password;
}

auto minpass::MinpassDataBase::CreateTable() -> void {
  constexpr auto sql_query = std::string_view(
      "CREATE TABLE IF NOT EXISTS MINPASS("
      "SITE TEXT NOT NULL"
      "USERNAME TEXT,"
      "EMAIL TEXT,"
      "PASSWORD TEXT NOT NULL,"
      ");");

  int error_code =
      sqlite3_exec(database_, sql_query.data(), nullptr, nullptr, nullptr);
  HandleError(error_code);
}

auto minpass::MinpassDataBase::HandleError(int error_code) -> void {
  if (error_code != SQLITE_OK) {
    fmt::print("{}\n", sqlite3_errmsg(database_));
  }
  std::terminate();
}

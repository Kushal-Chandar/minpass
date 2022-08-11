#include <fmt/core.h>
#include <sqlite3.h>

#include <coroutine>
#include <cstddef>
#include <exception>
#include <span>
#include <string_view>

#include "minpass/minpass.h"

static auto callback(void *greet, int argc, char **argv, char **azColName)
    -> int {
  fmt::print("{}\n", static_cast<const char *>(greet));
  for (int arg = 0; arg < argc; arg++) {
    fmt::print("{} = {}\n", azColName[arg],
               static_cast<bool>(argv[arg]) ? argv[arg] : "NULL");
  }
  fmt::print("\n");
  return 0;
}

auto main(/* int argc, char const* argv[] */) -> int {
  int sqlite_exit = 0;
  sqlite3 *data_base = nullptr;
  sqlite3_open("test.db", &data_base);
  char *error_message = nullptr;

  constexpr auto sql_create = std::string_view(
      "CREATE TABLE IF NOT EXISTS GRADES("
      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
      "NAME TEXT NOT NULL,"
      "LNAME TEXT NOT NULL,"
      "AGE INT NOT NULL,"
      "ADDRESS CHAR(50),"
      "GRADE CHAR(1)"
      ");");

  sqlite_exit = sqlite3_exec(data_base, sql_create.data(), nullptr, nullptr,
                             &error_message);
  sqlite3_free(error_message);
  if (sqlite_exit != SQLITE_OK) {
    fmt::print("{}", error_message);
  }

  constexpr auto sql_add = std::string_view(
      "INSERT INTO GRADES (NAME, LNAME, AGE, GRADE) VALUES('Kushal', "
      "'Chandar', 19, 'O');"
      "INSERT INTO GRADES (NAME, LNAME, AGE, GRADE) VALUES('Pardhu', "
      "'Lonka', 20, 'O');"
      "INSERT INTO GRADES (NAME, LNAME, AGE, GRADE) VALUES('Sai', "
      "'Kiran', 19, 'O');");

  error_message = nullptr;
  sqlite_exit =
      sqlite3_exec(data_base, sql_add.data(), nullptr, nullptr, &error_message);
  sqlite3_free(error_message);
  if (sqlite_exit != SQLITE_OK) {
    fmt::print("{}", error_message);
  }

  constexpr auto sql_select =
      std::string_view("SELECT NAME, AGE, GRADE FROM GRADES;");

  error_message = nullptr;
  sqlite_exit = sqlite3_exec(data_base, sql_select.data(), callback,
                             static_cast<void *>("Hello"), &error_message);
  sqlite3_free(error_message);
  if (sqlite_exit != SQLITE_OK) {
    fmt::print("{}", error_message);
  }

  sqlite3_close(data_base);

  minpass::MinpassDataBase abc(std::string_view("Hello"));

  return 0;
}

#include "sqlite3_client.h"

#include <drogon/drogon.h>

#include "minpass_types.h"

minpass::SQLite3Client::SQLite3Client() {
  auto client = drogon::app().getDbClient();
  client->execSqlAsync(
      "CREATE TABLE Persons ("
      "  Website varchar(100) NOT NULL PRIMARY KEY,"
      "  Email varchar(50),"
      "  UserName varchar(100),"
      "  Password varchar(50) NOT NULL,"
      ");",
      [](const drogon::orm::Result &result) {
        std::cout << result.size() << " rows selected!" << std::endl;
        int i = 0;
        for (auto row : result) {
          std::cout << i++ << ": user name is "
                    << row["user_name"].as<std::string>() << std::endl;
        }
      },
      [](const drogon::orm::DrogonDbException &e) {
        std::cerr << "error:" << e.base().what() << std::endl;
      },
      "default");
}

auto minpass::SQLite3Client::SetPassword(
    const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    Website website, Email email, std::string username, Password password)
    -> void {
  auto db_client = drogon::app().getDbClient();

  db_client->execSqlAsync("INSERT INTO table_name
                                VALUES (value1, value2, value3, ...)", )

clientPtr->execSqlAsync("select * from users where org_name=$1",
                            [](const drogon::orm::Result &result) {
    std::cout << result.size() << " rows selected!" << std::endl;
    int i = 0;
    for (auto row : result) {
      std::cout << i++ << ": user name is "
                << row["user_name"].as<std::string>() << std::endl;
    }
                            },
                            [](const DrogonDbException &e) {
    std::cerr << "error:" << e.base().what() << std::endl;
                            },
                            "default");

  Json::Value ret;
  ret["result"] = "ok";
  ret["token"] = drogon::utils::getUuid();
  auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
  callback(resp);
}

auto minpass::SQLite3Client::GetPassword(
    const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback,
    Website website) const -> void {}

#include "sqlite3_queries.h"

#include <drogon/drogon_test.h>

#define TABLE_NAME "minpass"  // change this if default table name is changed

DROGON_TEST(SQLite3QueriesTests_Queries_Case1) {
  // Testing
  // 1. Even number of single quotes in a post/patch request

  minpass::SQLite3Queries test_factory;
  auto website = minpass::Website("google.com");
  auto email = minpass::Email("abc@def.com");
  auto username = minpass::Username("12'34'5");
  auto password = minpass::Password();

  auto res =
      test_factory.CreatePasswordQuery(website, email, username, password);
  REQUIRE(res == "INSERT INTO " TABLE_NAME
                 "\n"
                 "VALUES ('google.com', 'abc@def.com', '12'34'5', '');\n");
  REQUIRE_NOTHROW(res ==
                  "INSERT INTO " TABLE_NAME
                  "\n"
                  "VALUES ('google.com', 'abc@def.com', '12'34'5', '');\n");
  // we are not executing the command yet so empty password should not throw
}

DROGON_TEST(SQLite3QueriesTests_Queries_Case2) {
  // Testing
  // 1. Odd number of single quotes in a post/patch request

  minpass::SQLite3Queries test_factory;
  auto website = minpass::Website("google.com");
  auto email = minpass::Email("abc@def.com");
  auto username = minpass::Username("12'345");
  auto password = minpass::Password("'");

  auto res =
      test_factory.CreatePasswordQuery(website, email, username, password);
  REQUIRE(res == "INSERT INTO " TABLE_NAME
                 "\n"
                 "VALUES ('google.com', 'abc@def.com', '12'345', ''');\n");
  REQUIRE_NOTHROW(res ==
                  "INSERT INTO " TABLE_NAME
                  "\n"
                  "VALUES ('google.com', 'abc@def.com', '12'345', ''');\n");
}

DROGON_TEST(SQLite3QueriesTests_Queries_Case3) {
  // Testing
  // 1. Testing '\' at the end

  minpass::SQLite3Queries test_factory;
  auto website = minpass::Website("google.com");
  auto email = minpass::Email("abc@def.com");
  auto username = minpass::Username("12'345\\");
  auto password = minpass::Password("'");

  auto res =
      test_factory.CreatePasswordQuery(website, email, username, password);
  REQUIRE(res == "INSERT INTO " TABLE_NAME
                 "\n"
                 "VALUES ('google.com', 'abc@def.com', '12'345\\', ''');\n");
  REQUIRE_NOTHROW(res ==
                  "INSERT INTO " TABLE_NAME
                  "\n"
                  "VALUES ('google.com', 'abc@def.com', '12'345\\', ''');\n");
}

#include "sqlite3_queries.h"

#include <drogon/drogon_test.h>

namespace minpass {

DROGON_TEST(SQLite3QueriesTests_Queries) {
  minpass::SQLite3Queries test_factory;
  auto website = minpass::Website("google.com");
  auto email = minpass::Email("abc@def.com");
  auto username = minpass::Username("'qw'we'we''ew'''we''we''w'e'w'we'w''");
  auto password = minpass::Password();

  test_factory.CreatePasswordQuery(website, email, username, password);

  // CHECK_NOTHROW(sqlite3_client::exception(error));
}

}  // namespace minpass

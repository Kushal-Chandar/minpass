#include "sqlite3_client/helpers.h"

#include <drogon/drogon_test.h>

namespace minpass::sqlite3_client {

DROGON_TEST(HelpersTests_CommonException) {
  const drogon::orm::DrogonDbException error;
  CHECK_NOTHROW(Helpers::CommonException(error));
}

}  // namespace minpass::sqlite3_client

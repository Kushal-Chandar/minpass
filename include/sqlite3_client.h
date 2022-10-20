#if !defined(MINPASS)
#define MINPASS

#include <drogon/drogon.h>

#include "minpass_types.h"

namespace minpass {
class SQLite3Client : public drogon::HttpController<SQLite3Client> {
 public:
  METHOD_LIST_BEGIN
  METHOD_ADD(SQLite3Client::SetPassword,
             "/?website={1}/email={2}&username={3}&password={4}", drogon::Post);
  METHOD_ADD(SQLite3Client::GetPassword, "/?website={1}/", drogon::Get);
  METHOD_LIST_END

  SQLite3Client();

  static auto SetPassword(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback,
      Website website, Email email, std::string username, Password password)
      -> void;
  ;
  static auto GetPassword(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback,
      Website website) -> void;
};
}  // namespace minpass

#endif  // MINPASS

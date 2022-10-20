#if !defined(MINPASS)
#define MINPASS

#include <drogon/drogon.h>

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
      std::string &&website, const std::string &email, std::string &&username,
      const std::string &password) -> void;
  ;
  static auto GetPassword(
      const drogon::HttpRequestPtr &req,
      std::function<void(const drogon::HttpResponsePtr &)> &&callback,
      std::string website) -> void;
};
}  // namespace minpass

#endif  // MINPASS

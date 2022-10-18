#if !defined(MINPASS)
#define MINPASS

#include <sqlite3.h>

#include <string_view>

namespace minpass {

struct Website {
  std::string_view value_;
};
struct Username {
  std::string_view value_;
};
struct Email {
  std::string_view value_;
};
struct Password {
  std::string_view value_;
};

/**
 * @brief a class to interface with minpass database
 *
 */
class MinpassDataBase {
 private:
  sqlite3* database_ = nullptr;
  auto HandleError(int error_code) -> void;
  auto CreateTable() -> void;

 public:
  MinpassDataBase();
  explicit MinpassDataBase(std::string_view& database_name);
  auto set_password(const Website& site, const Username& username,
                    const Email& email, const Password& password) -> void;
  auto get_password(const Website& site) -> std::vector<std::string_view>;
  ~MinpassDataBase();
};

}  // namespace minpass

#endif  // MINPASS

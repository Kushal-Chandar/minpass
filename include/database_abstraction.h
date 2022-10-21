#if !defined(DATABASE_ABSTRACTION)
#define DATABASE_ABSTRACTION

#include <drogon/drogon.h>

#include "minpass_types.h"

namespace minpass {
class DatabaseAbstraction {
  auto CreateTable(std::string_view name) -> void;
  auto InsertPassword(Website& website, Email& email, Username&, Password&)
      -> void;
  auto RetrievePassword(Website& website) -> void;
};
}  // namespace minpass

#endif  // DATABASE_ABSTRACTION

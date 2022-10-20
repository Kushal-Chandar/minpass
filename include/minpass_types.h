#if !defined(TYPES)
#define TYPES

#include <string>

#include "utilities/strong_types.h"
namespace minpass {
using Email = utilities::StrongType<std::string, struct EmailParam>;
using Website = utilities::StrongType<std::string, struct WebsiteParam>;
using Username = utilities::StrongType<std::string, struct UsernameParam>;
using Password = utilities::StrongType<std::string, struct PasswordParam>;
}  // namespace minpass

#endif  // TYPES

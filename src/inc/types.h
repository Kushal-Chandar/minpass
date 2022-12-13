#if !defined(MINPASS_SRC_INC_MINPASS_TYPES_H_)
#define MINPASS_SRC_INC_MINPASS_TYPES_H_

#include <sstream>
#include <string>

#include "utilities/strong_types.h"

namespace minpass {

using Email = utilities::StrongType<std::string, struct EmailParam>;
using Website = utilities::StrongType<std::string, struct WebsiteParam>;
using Username = utilities::StrongType<std::string, struct UsernameParam>;
using Password = utilities::StrongType<std::string, struct PasswordParam>;
using MasterPassword =
    utilities::StrongType<std::string, struct MasterPasswordParam>;
using DatabaseName = utilities::StrongType<std::string, struct DatabaseParam>;
using TableName = utilities::StrongType<std::string, struct TableParam>;

// Overloads
template <typename Type, typename Tag>
auto operator>>(std::stringstream& string_stream,
                minpass::utilities::StrongType<Type, Tag>& minpass_type)
    -> std::stringstream& {
  std::string value;
  string_stream >> value;
  minpass_type.set(std::move(value));
  return string_stream;
}

}  // namespace minpass

#endif  // MINPASS_SRC_INC_MINPASS_TYPES_H_

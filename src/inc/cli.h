#if !defined(MINPASS_SRC_INC_CLI_H_)
#define MINPASS_SRC_INC_CLI_H_

#include <optional>

namespace minpass {

class CLI {
 public:
  static auto Parse(int argc, char const **argv) noexcept -> std::optional<int>;
};

}  // namespace minpass

#endif  // MINPASS_SRC_INC_CLI_H_

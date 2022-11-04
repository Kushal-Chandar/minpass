#if !defined(SCRYPT_KDF)
#define SCRYPT_KDF

#include <string>

namespace minpass::utilities {

class ScryptKDF {
 public:
  static auto GenerateKey(const std::string &password) -> void;
};

}  // namespace minpass::utilities

#endif  // SCRYPT_KDF

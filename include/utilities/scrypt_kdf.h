#if !defined(SCRYPT_KDF)
#define SCRYPT_KDF

#include <string>
#include <tuple>

namespace minpass::utilities {

class ScryptKDF {
 public:
  static auto GenerateKeyAndIV(const std::string &password)
      -> std::tuple<std::string, std::string>;

 private:
  static constexpr int kKeySize_ = 32;
  static constexpr int kIVSize_ = 16;
  static constexpr int kSaltSize_ = 8;
  static constexpr int kCost_ = 1024;
  static constexpr int kBlockSize_ = 8;
  static constexpr int kParallelization_ = 16;
};

}  // namespace minpass::utilities

#endif  // SCRYPT_KDF

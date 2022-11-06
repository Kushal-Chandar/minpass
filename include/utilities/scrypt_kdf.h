#if !defined(SCRYPT_KDF)
#define SCRYPT_KDF

#include <cryptopp/config_int.h>  // for byte
#include <cryptopp/secblock.h>    // for SecByteBlock

#include <tuple>   // for tuple
#include <vector>  // for vector

namespace minpass::utilities {

class ScryptKDF {
 public:
  static auto GenerateKeyAndIV(
      const std::vector<CryptoPP::byte>& password_bytes)
      -> std::tuple<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock,
                    CryptoPP::SecByteBlock>;

  static auto GetStringFromBytes(const std::vector<CryptoPP::byte>& bytes_in)
      -> std::string;
  static auto GetBytesFromString(const std::string& string_in)
      -> std::vector<CryptoPP::byte>;

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

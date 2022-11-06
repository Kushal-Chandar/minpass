#if !defined(SCRYPT_KDF)
#define SCRYPT_KDF

#include <cryptopp/config_int.h>  // for byte
#include <cryptopp/secblock.h>    // for SecByteBlock

#include <tuple>   // for tuple
#include <vector>  // for vector

namespace minpass::minpass_crypto {

class ScryptKDF {
 public:
  static auto GenerateKeyAndIV(
      const std::vector<CryptoPP::byte>& password_bytes)
      -> std::tuple<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock,
                    CryptoPP::SecByteBlock>;

 private:
  static constexpr int kKeySize_ = 32;
  static constexpr int kIVSize_ = 16;
  static constexpr int kSaltSize_ = 8;
  static constexpr int kCost_ = 1024;
  static constexpr int kBlockSize_ = 8;
  static constexpr int kParallelization_ = 16;
};

}  // namespace minpass::minpass_crypto

#endif  // SCRYPT_KDF

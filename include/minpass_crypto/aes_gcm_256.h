#if !defined(MINPASS_INCLUDE_MINPASS_CRYPTO_AES_GCM_256_H_)
#define MINPASS_INCLUDE_MINPASS_CRYPTO_AES_GCM_256_H_

#include <string>

namespace minpass::minpass_crypto {

class AES_GCM_256 {
 public:
  static auto encrypt(const std::string& plain_text) -> std::string;
  static auto decrypt(const std::string& cipher_text) -> std::string;

 private:
  static constexpr int kTagSize_ = 12;
};

}  // namespace minpass::minpass_crypto

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_AES_GCM_256_H_

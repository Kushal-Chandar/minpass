#if !defined(MINPASS_INCLUDE_MINPASS_CRYPTO_AES_GCM_256_H_)
#define MINPASS_INCLUDE_MINPASS_CRYPTO_AES_GCM_256_H_

#include <string>

#include "minpass_crypto.h"

namespace minpass::minpass_crypto {

class AES_GCM_256 : public minpass::MinpassCrypto {
 public:
  AES_GCM_256(std::string key);
  auto Encrypt(const std::string& plain_text) -> std::string override;
  auto Decrypt(const std::string& cipher_text) -> std::string override;

 private:
  const std::string kKey_;
  const int kTagSize_ = 16;  // Secure tag size for AES_GCM_256
  static auto GetCipherSize(size_t cipher_size, int salt_size, int iv_size)
      -> size_t;
};

}  // namespace minpass::minpass_crypto

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_AES_GCM_256_H_

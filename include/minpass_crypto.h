#if !defined(MINPASS_INCLUDE_MINPASS_CRYPTO_H_)
#define MINPASS_INCLUDE_MINPASS_CRYPTO_H_

#include <string>

namespace minpass {

class MinpassCrypto {
 public:
  virtual auto Encrypt(const std::string &plain_text) -> std::string = 0;
  virtual auto Decrypt(const std::string &cipher_text) -> std::string = 0;
  virtual ~MinpassCrypto() = default;
};

}  // namespace minpass

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_H_

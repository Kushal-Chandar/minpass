#if !defined(MINPASS_INCLUDE_MINPASS_CRYPTO_H_)
#define MINPASS_INCLUDE_MINPASS_CRYPTO_H_

#include <string>

namespace minpass {

class MinpassCrypto {
 public:
  virtual auto encrypt(const std::string &plain_text) -> std::string = 0;
  virtual auto decrypt(const std::string &chipher_text) -> std::string = 0;
  virtual ~MinpassCrypto() = default;
};

class MinpassCryptoAESGCM256 : public MinpassCrypto {
 public:
  auto encrypt(const std::string &plain_text) -> std::string override;
  auto decrypt(const std::string &chipher_text) -> std::string override;
};

}  // namespace minpass

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_H_

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

class MinpassCryptoFactory {
 public:
  template <class CryptographicClass>
  static auto CreateMinpassCrypto(const std::string &master_password)
      -> std::unique_ptr<MinpassCrypto> {
    return std::make_unique<CryptographicClass>(master_password);
  }
};

}  // namespace minpass

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_H_

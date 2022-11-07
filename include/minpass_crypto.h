#if !defined(MINPASS_INCLUDE_MINPASS_CRYPTO_H_)
#define MINPASS_INCLUDE_MINPASS_CRYPTO_H_

#include <string>

namespace minpass {

class MinpassCrypto {
 public:
  static auto encrypt(const std::string &plain_text) -> std::string;
  static auto decrypt(const std::string &chipher_text) -> std::string;
};

}  // namespace minpass

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_H_

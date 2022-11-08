#if !defined(MINPASS_INCLUDE_MINPASS_CRYPTO_AES_GCM_256_H_)
#define MINPASS_INCLUDE_MINPASS_CRYPTO_AES_GCM_256_H_

#include <cryptopp/secblock.h>

namespace minpass::minpass_crypto {

class AES_GCM_256 {
 public:
  static auto encrypt(const CryptoPP::SecByteBlock& plain_bytes_in,
                      CryptoPP::SecByteBlock& cipher_bytes_out) -> bool;
  static auto decrypt(const CryptoPP::SecByteBlock& cipher_bytes_in,
                      CryptoPP::SecByteBlock& plain_bytes_out) -> bool;

 private:
  static constexpr int kTagSize_ = 12;
  static auto pretty_print(const CryptoPP::SecByteBlock& text) -> void;
};

}  // namespace minpass::minpass_crypto

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_AES_GCM_256_H_

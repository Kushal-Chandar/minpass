#if !defined(MINPASS_INCLUDE_MINPASS_CRYPTO_SCRYPT_KDF_H_)
#define MINPASS_INCLUDE_MINPASS_CRYPTO_SCRYPT_KDF_H_

#include <cryptopp/config_int.h>  // for byte
#include <cryptopp/secblock.h>    // for SecByteBlock

#include <tuple>  // for tuple

namespace minpass::minpass_crypto {

class ScryptKDF {
 public:
  static auto GetEncryptionKeyAndIV(
      const CryptoPP::SecByteBlock& password_bytes)
      -> std::tuple<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock,
                    CryptoPP::SecByteBlock>;
  static auto AddSaltAndIVToCipher(
      CryptoPP::SecByteBlock& salt,
      CryptoPP::SecByteBlock& initialization_vector, std::string& cipher_text)
      -> void;
  static auto SeperateSaltAndIVFromCipher(
      const std::string& cipher_text_with_key_and_iv)
      -> std::tuple<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock>;

  static const int kKeySize_ = 32;
  static const int kIVSize_ = 16;
  static const int kSaltSize_ = 8;

 private:
  static const int kCost_ = 1024;
  static const int kBlockSize_ = 8;
  static const int kParallelization_ = 16;
};

}  // namespace minpass::minpass_crypto

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_SCRYPT_KDF_H_

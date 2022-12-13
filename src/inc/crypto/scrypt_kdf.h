#if !defined(MINPASS_SRC_INC_CRYPTO_SCRYPT_KDF_H_)
#define MINPASS_SRC_INC_CRYPTO_SCRYPT_KDF_H_

#include <cryptopp/config_int.h>  // for byte
#include <cryptopp/secblock.h>    // for SecByteBlock

#include <tuple>  // for tuple

namespace minpass::crypto {

class ScryptKDF {
 public:
  static auto GetEncryptionKeySaltIV(
      const CryptoPP::SecByteBlock& password_bytes)
      -> std::tuple<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock,
                    CryptoPP::SecByteBlock>;
  static auto GetDecryptionKey(const CryptoPP::SecByteBlock& password_bytes,
                               const CryptoPP::SecByteBlock& salt)
      -> CryptoPP::SecByteBlock;
  static auto AddSaltAndIVToCipher(
      CryptoPP::SecByteBlock& salt,
      CryptoPP::SecByteBlock& initialization_vector, std::string& cipher_text)
      -> void;
  static auto GetSaltAndIVFromCipher(
      const std::string& cipher_text_with_salt_and_iv)
      -> std::tuple<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock>;

  static const int kKeySize_ = 32;  // 256 bits
  static const int kIVSize_ = 12;   // 96 bits recommended sizes
  static const int kSaltSize_ = 8;  // 32 bits recommended sizes

 private:
  static const int kCost_ = 1024;
  static const int kBlockSize_ = 8;
  static const int kParallelization_ = 16;
};

}  // namespace minpass::crypto

#endif  // MINPASS_SRC_INC_CRYPTO_SCRYPT_KDF_H_

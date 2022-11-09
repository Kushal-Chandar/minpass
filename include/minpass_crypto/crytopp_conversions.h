#if !defined(MINPASS_INCLUDE_MINPASS_CRYPTO_CRYPTOPP_CONVERSIONS_H_)
#define MINPASS_INCLUDE_MINPASS_CRYPTO_CRYPTOPP_CONVERSIONS_H_

#include <cryptopp/scrypt.h>
#include <cryptopp/secblock.h>  // for SecByteBlock

#include <string>  // for string

namespace minpass::minpass_crypto {

class CryptoppConversions {
 public:
  static auto GetStringFromSecByteBlock(const CryptoPP::SecByteBlock& bytes_in)
      -> std::string;
  static auto GetSecByteBlockFromString(const std::string& string_in)
      -> CryptoPP::SecByteBlock;
  static auto AddSaltAndIVToCipher(
      CryptoPP::SecByteBlock& salt,
      CryptoPP::SecByteBlock& initialization_vector, std::string& cipher_text)
      -> void;
};

}  // namespace minpass::minpass_crypto

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_CRYPTOPP_CONVERSIONS_H_

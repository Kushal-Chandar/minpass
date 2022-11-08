#if !defined(MINPASS_INCLUDE_MINPASS_CRYPTO_CRYPTOPP_CONVERSIONS_H_)
#define MINPASS_INCLUDE_MINPASS_CRYPTO_CRYPTOPP_CONVERSIONS_H_

#include <cryptopp/secblock.h>  // for SecByteBlock

#include <string>  // for string

namespace minpass::minpass_crypto {

class CryptoppConversions {
 public:
  static auto GetStringFromSecByteBlock(const CryptoPP::SecByteBlock& bytes_in)
      -> std::string;
  static auto GetSecByteBlockFromString(const std::string& string_in)
      -> CryptoPP::SecByteBlock;
};

}  // namespace minpass::minpass_crypto

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_CRYPTOPP_CONVERSIONS_H_

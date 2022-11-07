#if !defined(MINPASS_INCLUDE_MINPASS_CRYPTO_CRYPTOPP_CONVERSIONS_H_)
#define MINPASS_INCLUDE_MINPASS_CRYPTO_CRYPTOPP_CONVERSIONS_H_

#include <cryptopp/config_int.h>  // for byte
#include <cryptopp/secblock.h>    // for SecByteBlock

#include <string>  // for string
#include <vector>  // for vector

namespace minpass::minpass_crypto {

class CryptoppConversions {
 public:
  static auto GetStringFromByteBlock(const CryptoPP::SecByteBlock& bytes_in)
      -> std::string;
  static auto GetByteBlockFromString(const std::string& string_in)
      -> CryptoPP::SecByteBlock;
};

}  // namespace minpass::minpass_crypto

#endif  // MINPASS_INCLUDE_MINPASS_CRYPTO_CRYPTOPP_CONVERSIONS_H_

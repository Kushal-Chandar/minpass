#if !defined(CRYPTOPP_CONVERSIONS)
#define CRYPTOPP_CONVERSIONS

#include <cryptopp/config_int.h>  // for byte
#include <cryptopp/secblock.h>    // for SecByteBlock

#include <string>  // for string
#include <vector>  // for vector

namespace minpass::minpass_crypto {

class CryptoppConversions {
 public:
  static auto GetStringFromBytes(const std::vector<CryptoPP::byte>& bytes_in)
      -> std::string;
  static auto GetBytesFromString(const std::string& string_in)
      -> std::vector<CryptoPP::byte>;
};

}  // namespace minpass::minpass_crypto

#endif  // CRYPTOPP_CONVERSIONS

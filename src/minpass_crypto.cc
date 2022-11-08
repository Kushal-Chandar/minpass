#include "minpass_crypto.h"

#include "cryptopp/secblock.h"
#include "minpass_crypto/aes_gcm_256.h"
#include "minpass_crypto/crytopp_conversions.h"

namespace minpass {

auto MinpassCrypto::encrypt(const std::string& plain_text) -> std::string {
  const auto plain_text_secure_bytes =
      minpass_crypto::CryptoppConversions::GetSecByteBlockFromString(
          plain_text);

  CryptoPP::SecByteBlock cipher_text_secure_bytes;

  minpass_crypto::AES_GCM_256::encrypt(plain_text_secure_bytes,
                                       cipher_text_secure_bytes);

  return minpass_crypto::CryptoppConversions::GetStringFromSecByteBlock(
      cipher_text_secure_bytes);
}

}  // namespace minpass

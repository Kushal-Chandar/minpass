#include "minpass_crypto.h"

#include "cryptopp/secblock.h"
#include "minpass_crypto/aes_gcm_256.h"
#include "minpass_crypto/crytopp_conversions.h"

namespace minpass {

auto MinpassCryptoAESGCM256::encrypt(const std::string& plain_text)
    -> std::string {
  return minpass_crypto::AES_GCM_256::encrypt(plain_text);
}

auto MinpassCryptoAESGCM256::decrypt(const std::string& plain_text)
    -> std::string {
  return minpass_crypto::AES_GCM_256::decrypt(plain_text);
}

}  // namespace minpass

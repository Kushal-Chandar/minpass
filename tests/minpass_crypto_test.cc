#include "minpass_crypto.h"

#include <drogon/drogon_test.h>

#include "minpass_crypto/aes_gcm_256.h"
#include "test_utilities/include/random_string_generator.h"

DROGON_TEST(MinpassCryptoFactoryTest) {
  // Testing:
  // MinpassCryptoFactory must create an object of type aes_gcm_256
  // This object must be able to encrypt and decrypt passwords
  auto master_password = std::string("8k23cc8k3298");  // Random password
  std::cout << minpass::tests::generate_random_string(34);
  auto crypto = minpass::MinpassCryptoFactory::CreateMinpassCrypto<
      minpass::minpass_crypto::AES_GCM_256>(master_password);
  auto password = std::string("This is very very long password");
  auto enc = crypto->Encrypt(password);
  auto dec = crypto->Decrypt(enc);
  CHECK(password == dec);
}

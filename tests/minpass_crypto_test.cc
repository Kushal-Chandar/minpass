#include "minpass_crypto.h"

#include <drogon/drogon_test.h>

#include "minpass_crypto/aes_gcm_256.h"
#include "test_utilities/random_string_generator.h"

const int kMasterPasswordLen = 20;
const int kPasswordLen = 30;

DROGON_TEST(MinpassCryptoFactoryTest) {
  // Testing:
  // MinpassCryptoFactory must create an object of type aes_gcm_256
  // This object must be able to encrypt and decrypt passwords

  auto master_password = minpass::tests::generate_random_string(
      kMasterPasswordLen);  // Random password
  auto crypto = minpass::MinpassCryptoFactory::CreateMinpassCrypto<
      minpass::minpass_crypto::AES_GCM_256>(master_password);
  auto password =
      minpass::tests::generate_random_string(kPasswordLen);  // Random password;
  auto enc = crypto->Encrypt(password);
  auto dec = crypto->Decrypt(enc);
  CHECK(password == dec);
}

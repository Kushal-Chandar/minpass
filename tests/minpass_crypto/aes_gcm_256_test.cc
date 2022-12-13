#include "crypto/aes_gcm_256.h"

#include <drogon/drogon_test.h>

#include "test_utilities/random_string_generator.h"

const int kMasterPasswordLen = 20;
const int kPasswordLen = 30;

DROGON_TEST(MinpassCryptoAESGCM256_EncryptionDecryptionTest_Case1) {
  // Testing:
  // Encryption and decryption of text where the encrypted text is not modifed

  // Expected:
  // Text must decrypt with as usual

  auto master_password =
      minpass::tests::generate_random_string(kMasterPasswordLen);
  minpass::crypto::AES_GCM_256 crypto(master_password);
  auto password = minpass::tests::generate_random_string(kPasswordLen);
  auto enc = crypto.Encrypt(password);
  auto dec = crypto.Decrypt(enc);
  CHECK(password == dec);
}

DROGON_TEST(MinpassCryptoAESGCM256_EncryptionDecryptionTest_Case2) {
  // Testing:
  // Encryption and decryption of text where the encrypted text is modifed

  // Expected:
  // Text must not decrypt

  auto master_password =
      minpass::tests::generate_random_string(kMasterPasswordLen);
  minpass::crypto::AES_GCM_256 crypto(master_password);
  auto password = minpass::tests::generate_random_string(kPasswordLen);
  auto enc = crypto.Encrypt(password);
  enc.push_back('i');
  auto dec = crypto.Decrypt(enc);
  CHECK(dec != password);
}

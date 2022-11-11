#include "minpass_crypto/scrypt_kdf.h"

#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/gcm.h>
#include <cryptopp/secblock.h>
#include <drogon/drogon_test.h>

#include "minpass_crypto/aes_gcm_256.h"
#include "minpass_crypto/crytopp_conversions.h"
#include "test_utilities/include/random_string_generator.h"

const int kMasterPasswordLen = 30;
const int kPlainLen = 30;
const int kCipherLen = 30;

DROGON_TEST(MinpassScrypt_EncryptionKeySaltIV_DecryptionKey) {
  // Testing:
  // EncryptionKeySaltIv and DecryptionKey must generate the same derived key

  const int tag_size = 16;

  auto password = minpass::tests::generate_random_string(kMasterPasswordLen);
  auto password_bytes =
      minpass::minpass_crypto::CryptoppConversions::GetSecByteBlockFromString(
          password);

  auto [derived_key1, salt, initialization_vector] =
      minpass::minpass_crypto::ScryptKDF::GetEncryptionKeySaltIV(
          password_bytes);

  // Generate same derived key using the salt
  auto derived_key2 = minpass::minpass_crypto::ScryptKDF::GetDecryptionKey(
      password_bytes, salt);

  CHECK(derived_key1 == derived_key2);
}

DROGON_TEST(MinpassScrypt_AddSaltAndIVToCipher_GetSaltAndIVFromCipher) {
  // Testing:
  // Get same salt, iv and cipher before adding and getting

  const int tag_size = 16;

  auto password = minpass::tests::generate_random_string(kMasterPasswordLen);
  auto cipher = minpass::tests::generate_random_string(kCipherLen);
  auto cipher_text(cipher);

  auto [derived_key1, salt1, iv1] =
      minpass::minpass_crypto::ScryptKDF::GetEncryptionKeySaltIV(
          minpass::minpass_crypto::CryptoppConversions::
              GetSecByteBlockFromString(password));

  minpass::minpass_crypto::ScryptKDF::AddSaltAndIVToCipher(salt1, iv1, cipher);

  auto [salt2, iv2] =
      minpass::minpass_crypto::ScryptKDF::GetSaltAndIVFromCipher(cipher);

  auto cipher_text_without_key_and_iv = cipher.substr(0, kCipherLen);

  CHECK(salt1 == salt2);
  CHECK(iv1 == iv2);
  CHECK(cipher_text == cipher_text_without_key_and_iv);
}

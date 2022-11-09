#include "minpass_crypto/aes_gcm_256.h"

#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/gcm.h>
#include <cryptopp/hex.h>
#include <cryptopp/secblock.h>
#include <fmt/core.h>

#include <iostream>
#include <string>

#include "minpass_crypto/crytopp_conversions.h"
#include "minpass_crypto/scrypt_kdf.h"

namespace minpass::minpass_crypto {

AES_GCM_256::AES_GCM_256(std::string key) : kKey_(std::move(key)) {}

auto AES_GCM_256::GetCipherSize(size_t cipher_size, int salt_size, int iv_size)
    -> size_t {
  return cipher_size - static_cast<size_t>(salt_size - iv_size);
}

auto AES_GCM_256::Encrypt(const std::string& plain_text) -> std::string {
  std::string cipher_text;
  try {
    CryptoPP::GCM<CryptoPP::AES>::Encryption encryption;

    // derive key and iv using scrypt, store salt for decryption
    auto [derived_key, salt, initialization_vector] =
        ScryptKDF::GetEncryptionKeySaltIV(
            CryptoppConversions::GetSecByteBlockFromString(kKey_));

    encryption.SetKeyWithIV(derived_key, ScryptKDF::kKeySize_,
                            initialization_vector, ScryptKDF::kIVSize_);

    // encrypt plain_text with tag and store in cipher_text
    const CryptoPP::StringSource encrypt_to_string(
        plain_text, true,
        new CryptoPP::AuthenticatedEncryptionFilter(
            encryption, new CryptoPP::StringSink(cipher_text), false,
            kTagSize_));

    std::cout << "encrypt function: " << cipher_text << '\n';

    // store salt and iv with cipher text
    ScryptKDF::AddSaltAndIVToCipher(salt, initialization_vector, cipher_text);

  } catch (CryptoPP::InvalidArgument& e) {
    fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
  } catch (CryptoPP::Exception& e) {
    fmt::print("Caught Exception...\n{}\n\n", e.what());
  }

  return cipher_text;
}

auto AES_GCM_256::Decrypt(const std::string& cipher_text) -> std::string {
  auto recovered_text = cipher_text.substr(
      0, GetCipherSize(cipher_text.size(), ScryptKDF::kSaltSize_,
                       ScryptKDF::kIVSize_));

  try {
    CryptoPP::GCM<CryptoPP::AES>::Decryption decryption;

    // Get salt and iv from cipher text
    auto [salt, initialization_vector] =
        ScryptKDF::SeperateSaltAndIVFromCipher(cipher_text);

    // Generate same derived key using the salt
    auto derived_key = ScryptKDF::GetDecryptionKey(
        CryptoppConversions::GetSecByteBlockFromString(kKey_), salt);

    decryption.SetKeyWithIV(derived_key, ScryptKDF::kKeySize_,
                            initialization_vector, ScryptKDF::kIVSize_);

    // CryptoPP::AuthenticatedDecryptionFilter df(
    //     decryption, new CryptoPP::StringSink(plain_),
    //     CryptoPP::AuthenticatedDecryptionFilter::DEFAULT_FLAGS,
    //     kTagSize_);  // AuthenticatedDecryptionFilter

    // // The StringSource dtor will be called immediately
    // //  after construction below. This will cause the
    // //  destruction of objects it owns. To stop the
    // //  behavior so we can get the decoding result from
    // //  the DecryptionFilter, we must use a redirector
    // //  or manually Put(...) into the filter without
    // //  using a StringSource.
    // CryptoPP::StringSource(
    //     aes_cipher_text, true,
    //     new CryptoPP::Redirector(df /*, PASS_EVERYTHING */));  //

    // // If the object does not throw, here's the only
    // //  opportunity to check the data's integrity
    // bool b = df.GetLastResult();

  } catch (CryptoPP::HashVerificationFilter::HashVerificationFailed& e) {
    fmt::print("Caught HashVerificationFailed...\n{}\n\n", e.what());
  } catch (CryptoPP::InvalidArgument& e) {
    fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
  } catch (CryptoPP::Exception& e) {
    fmt::print("Caught Exception...\n{}\n\n", e.what());
  }

  return recovered_text;
}

}  // namespace minpass::minpass_crypto

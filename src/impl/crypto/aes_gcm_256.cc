#include "crypto/aes_gcm_256.h"

#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/gcm.h>
#include <cryptopp/secblock.h>
#include <fmt/color.h>

#include <iostream>
#include <string>

#include "crypto/crytopp_conversions.h"
#include "crypto/scrypt_kdf.h"

namespace minpass::crypto {

AES_GCM_256::AES_GCM_256(std::string key) : kKey_(std::move(key)) {}

auto AES_GCM_256::GetCipherSize(size_t cipher_size, int salt_size, int iv_size)
    -> size_t {
  return cipher_size - static_cast<size_t>(salt_size + iv_size);
}

auto AES_GCM_256::Encrypt(const std::string& plain_text) -> std::string {
  std::string cipher_text;
  try {
    CryptoPP::GCM<CryptoPP::AES>::Encryption encryptor;

    // derive key and iv using scrypt, store salt for decryption
    auto [derived_key, salt, initialization_vector] =
        ScryptKDF::GetEncryptionKeySaltIV(
            CryptoppConversions::GetSecByteBlockFromString(kKey_));

    encryptor.SetKeyWithIV(derived_key, ScryptKDF::kKeySize_,
                           initialization_vector, ScryptKDF::kIVSize_);

    // encrypt plain_text with tag and store in cipher_text
    const CryptoPP::StringSource encrypt_to_string(
        plain_text, true,
        new CryptoPP::AuthenticatedEncryptionFilter(
            encryptor, new CryptoPP::StringSink(cipher_text), false,
            kTagSize_));

    // store salt and iv with cipher text
    ScryptKDF::AddSaltAndIVToCipher(salt, initialization_vector, cipher_text);

  } catch (CryptoPP::InvalidArgument& e) {
    fmt::print(fmt::fg(fmt::color::red), "Caught InvalidArgument...\n{}\n\n",
               e.what());
  } catch (CryptoPP::Exception& e) {
    fmt::print(fmt::fg(fmt::color::red), "Caught Exception...\n{}\n\n",
               e.what());
  }

  return cipher_text;
}

auto AES_GCM_256::Decrypt(const std::string& cipher_text) -> std::string {
  auto cipher_text_without_key_and_iv = cipher_text.substr(
      0, GetCipherSize(cipher_text.size(), ScryptKDF::kSaltSize_,
                       ScryptKDF::kIVSize_));

  std::string recovered_text;
  try {
    CryptoPP::GCM<CryptoPP::AES>::Decryption decryptor;

    // Get salt and iv from cipher text
    auto [salt, initialization_vector] =
        ScryptKDF::GetSaltAndIVFromCipher(cipher_text);

    // Generate same derived key using the salt
    auto derived_key = ScryptKDF::GetDecryptionKey(
        CryptoppConversions::GetSecByteBlockFromString(kKey_), salt);

    decryptor.SetKeyWithIV(derived_key, ScryptKDF::kKeySize_,
                           initialization_vector, ScryptKDF::kIVSize_);

    // Decrypt to string
    const CryptoPP::StringSource decrypt_to_string(
        cipher_text_without_key_and_iv, true,
        new CryptoPP::AuthenticatedDecryptionFilter(
            decryptor, new CryptoPP::StringSink(recovered_text),
            CryptoPP::AuthenticatedDecryptionFilter::DEFAULT_FLAGS, kTagSize_));

  } catch (CryptoPP::HashVerificationFilter::HashVerificationFailed& e) {
    fmt::print(fmt::fg(fmt::color::red),
               "Caught HashVerificationFailed...\n{}\n\n", e.what());
  } catch (CryptoPP::InvalidArgument& e) {
    fmt::print(fmt::fg(fmt::color::red), "Caught InvalidArgument...\n{}\n\n",
               e.what());
  } catch (CryptoPP::Exception& e) {
    fmt::print(fmt::fg(fmt::color::red), "Caught Exception...\n{}\n\n",
               e.what());
  }

  return recovered_text;
}

}  // namespace minpass::crypto

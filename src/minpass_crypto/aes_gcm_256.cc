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

auto AES_GCM_256::encrypt(const std::string& plain_text) -> std::string {
  std::string cipher_text;
  try {
    CryptoPP::GCM<CryptoPP::AES>::Encryption encryption;

    // derive key and iv using scrypt, store salt for decryption
    auto [key, salt, initialization_vector] = ScryptKDF::GetEncryptionKeyAndIV(
        CryptoppConversions::GetSecByteBlockFromString(plain_text));

    encryption.SetKeyWithIV(key, ScryptKDF::kKeySize_, initialization_vector,
                            ScryptKDF::kIVSize_);

    // encrypt plain_text with tag and store in cipher_text
    const CryptoPP::StringSource encrypt_to_string(
        plain_text, true,
        new CryptoPP::AuthenticatedEncryptionFilter(
            encryption, new CryptoPP::StringSink(cipher_text), false,
            kTagSize_));

    // store salt and iv with cipher text
    ScryptKDF::AddSaltAndIVToCipher(salt, initialization_vector, cipher_text);

    std::cout << "encrypt function: " << cipher_text << '\n';
    std::cout << "encrypt function: "
              << CryptoppConversions::GetStringFromSecByteBlock(salt)
              << "      ";
    std::cout << CryptoppConversions::GetStringFromSecByteBlock(
                     initialization_vector)
              << '\n';

  } catch (CryptoPP::InvalidArgument& e) {
    fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
  } catch (CryptoPP::Exception& e) {
    fmt::print("Caught Exception...\n{}\n\n", e.what());
  }

  return cipher_text;
}

auto AES_GCM_256::decrypt(const std::string& cipher_text) -> std::string {
  std::string recovered_text;

  auto [salt, iv] = ScryptKDF::SeperateSaltAndIVFromCipher(cipher_text);
  std::cout << "decrypt function: " << cipher_text << '\n';
  std::cout << "decrypt function: "
            << CryptoppConversions::GetStringFromSecByteBlock(salt) << "      ";
  std::cout << CryptoppConversions::GetStringFromSecByteBlock(iv) << '\n';
  // try {
  // CryptoPP::GCM<CryptoPP::AES>::Decryption decryption;

  // auto [key, initialization_vector, salt] =
  //     ScryptKDF::GetDecryptionKeyAndIV(plain_text_bytes);

  // decryption.SetKeyWithIV(key, sizeof(key), initialization_vector,
  //                         sizeof(initialization_vector));

  //   CryptoPP::AuthenticatedDecryptionFilter df(
  //       decryption, new CryptoPP::StringSink(plain_),
  //       CryptoPP::AuthenticatedDecryptionFilter::DEFAULT_FLAGS,
  //       kTagSize_);  // AuthenticatedDecryptionFilter

  //   // The StringSource dtor will be called immediately
  //   //  after construction below. This will cause the
  //   //  destruction of objects it owns. To stop the
  //   //  behavior so we can get the decoding result from
  //   //  the DecryptionFilter, we must use a redirector
  //   //  or manually Put(...) into the filter without
  //   //  using a StringSource.
  //   CryptoPP::StringSource(
  //       aes_cipher_text, true,
  //       new CryptoPP::Redirector(df /*, PASS_EVERYTHING */));  //

  //   // If the object does not throw, here's the only
  //   //  opportunity to check the data's integrity
  //   bool b = df.GetLastResult();

  // } catch (CryptoPP::HashVerificationFilter::HashVerificationFailed& e) {
  //   fmt::print("Caught HashVerificationFailed...\n{}\n\n", e.what());
  // } catch (CryptoPP::InvalidArgument& e) {
  //   fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
  // } catch (CryptoPP::Exception& e) {
  //   fmt::print("Caught Exception...\n{}\n\n", e.what());
  // }

  return recovered_text;
}

}  // namespace minpass::minpass_crypto

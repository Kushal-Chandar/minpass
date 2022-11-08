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

auto AES_GCM_256::encrypt(const std::string& plain_text_in) -> std::string {
  std::string cipher_text;
  try {
    CryptoPP::GCM<CryptoPP::AES>::Encryption encryption;

    auto [key, salt, initialization_vector] = ScryptKDF::GetEncryptionKeyAndIV(
        CryptoppConversions::GetSecByteBlockFromString(plain_text_in));

    encryption.SetKeyWithIV(key, sizeof(key), initialization_vector,
                            sizeof(initialization_vector));

    CryptoPP::StringSource(
        plain_text_in, true,
        new CryptoPP::AuthenticatedEncryptionFilter(
            encryption, new CryptoPP::StringSink(cipher_text), false,
            kTagSize_));

    std::cout << "Salt: "
              << minpass_crypto::CryptoppConversions::GetStringFromSecByteBlock(
                     salt)
                     .size()
              << '\n';
    std::cout << "IV: "
              << minpass_crypto::CryptoppConversions::GetStringFromSecByteBlock(
                     initialization_vector)
                     .size()
              << '\n';
    std::cout << "Cipher: " << cipher_text.size() << '\n';

  } catch (CryptoPP::InvalidArgument& e) {
    fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
  } catch (CryptoPP::Exception& e) {
    fmt::print("Caught Exception...\n{}\n\n", e.what());
  }

  return cipher_text;
}

auto AES_GCM_256::decrypt(const std::string& cipher_text_in) -> std::string {
  // try {
  //   CryptoPP::GCM<CryptoPP::AES>::Decryption decryption;

  //   auto plain_text_bytes = CryptoppConversions::GetBytesFromString(plain_);

  //   auto [key, initialization_vector, salt] =
  //       ScryptKDF::GetDecryptionKeyAndIV(plain_text_bytes);

  //   decryption.SetKeyWithIV(key, sizeof(key), initialization_vector,
  //                           sizeof(initialization_vector));

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

  //   fmt::print("recovered text: {}\n", plain_);

  // } catch (CryptoPP::HashVerificationFilter::HashVerificationFailed& e) {
  //   fmt::print("Caught HashVerificationFailed...\n{}\n\n", e.what());
  // } catch (CryptoPP::InvalidArgument& e) {
  //   fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
  // } catch (CryptoPP::Exception& e) {
  //   fmt::print("Caught Exception...\n{}\n\n", e.what());
  // }

  return std::string("");
}

}  // namespace minpass::minpass_crypto

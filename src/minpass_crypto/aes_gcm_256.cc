#include "minpass_crypto/aes_gcm_256.h"

#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/gcm.h>
#include <cryptopp/hex.h>
#include <fmt/core.h>

#include <iostream>
#include <string>

#include "minpass_crypto/scrypt_kdf.h"

namespace minpass::minpass_crypto {

auto AES_GCM_256::pretty_print(const std::string& text) -> void {
  std::string encoded;
  encoded.clear();
  {
    const CryptoPP::StringSource printer(
        text, true,
        new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
  }
  fmt::print("cipher text: {}\n", encoded);
}

auto AES_GCM_256::encrypt(const std::string& plain_text,
                          std::string& cipher_text) -> bool {
  try {
    fmt::print("plain text: {}\n", plain_text);
    CryptoPP::GCM<CryptoPP::AES>::Encryption encryption;

    auto plain_text_bytes = CryptoppConversions::GetBytesFromString(plain_text);

    auto [key, salt, initialization_vector] =
        ScryptKDF::GetEncryptionKeyAndIV(plain_text_bytes);

    encryption.SetKeyWithIV(key, sizeof(key), initialization_vector,
                            sizeof(initialization_vector));

    CryptoPP::StringSource(
        plain_text, true,
        new CryptoPP::AuthenticatedEncryptionFilter(
            encryption, new CryptoPP::StringSink(cipher_text), false,
            kTagSize_));

    CryptoPP::byte;

    std::cout << cipher_text << " + "
              << CryptoppConversions::GetStringFromBytes(
                     std::vector<CryptoPP::byte>(salt.data()))
              << '\n';

  } catch (CryptoPP::InvalidArgument& e) {
    fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
  } catch (CryptoPP::Exception& e) {
    fmt::print("Caught Exception...\n{}\n\n", e.what());
  }

  pretty_print(cipher_text);

  return true;
}

auto AES_GCM_256::decrypt(const std::string& cipher_text,
                          std::string& plain_text) -> bool {
  try {
    CryptoPP::GCM<CryptoPP::AES>::Decryption decryption;

    auto plain_text_bytes = CryptoppConversions::GetBytesFromString(plain_text);

    auto [key, initialization_vector, salt] =
        ScryptKDF::GetDecryptionKeyAndIV(plain_text_bytes);

    decryption.SetKeyWithIV(key, sizeof(key), initialization_vector,
                            sizeof(initialization_vector));

    CryptoPP::AuthenticatedDecryptionFilter df(
        decryption, new CryptoPP::StringSink(plain_text),
        CryptoPP::AuthenticatedDecryptionFilter::DEFAULT_FLAGS,
        kTagSize_);  // AuthenticatedDecryptionFilter

    // The StringSource dtor will be called immediately
    //  after construction below. This will cause the
    //  destruction of objects it owns. To stop the
    //  behavior so we can get the decoding result from
    //  the DecryptionFilter, we must use a redirector
    //  or manually Put(...) into the filter without
    //  using a StringSource.
    CryptoPP::StringSource(
        cipher_text, true,
        new CryptoPP::Redirector(df /*, PASS_EVERYTHING */));  //

    // If the object does not throw, here's the only
    //  opportunity to check the data's integrity
    bool b = df.GetLastResult();

    fmt::print("recovered text: {}\n", plain_text);

  } catch (CryptoPP::HashVerificationFilter::HashVerificationFailed& e) {
    fmt::print("Caught HashVerificationFailed...\n{}\n\n", e.what());
  } catch (CryptoPP::InvalidArgument& e) {
    fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
  } catch (CryptoPP::Exception& e) {
    fmt::print("Caught Exception...\n{}\n\n", e.what());
  }

  return true;
}

}  // namespace minpass::minpass_crypto

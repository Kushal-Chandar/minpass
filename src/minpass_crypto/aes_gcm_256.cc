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

auto AES_GCM_256::pretty_print(const CryptoPP::SecByteBlock& text) -> void {
  CryptoPP::SecByteBlock encoded;
  {
    const CryptoPP::StringSource printer(
        text, text.size(), true,
        new CryptoPP::HexEncoder(new CryptoPP::FileSink(std::cout)));
  }
}

auto AES_GCM_256::encrypt(const CryptoPP::SecByteBlock& plain_bytes_in,
                          CryptoPP::SecByteBlock& cipher_bytes_out) -> bool {
  try {
    CryptoPP::GCM<CryptoPP::AES>::Encryption encryption;

    auto [key, salt, initialization_vector] =
        ScryptKDF::GetEncryptionKeyAndIV(plain_bytes_in);

    encryption.SetKeyWithIV(key, sizeof(key), initialization_vector,
                            sizeof(initialization_vector));

    CryptoPP::ByteQueue plain_queue, cipher_queue;
    plain_queue.Put(plain_bytes_in, plain_bytes_in.size());

    CryptoPP::AuthenticatedEncryptionFilter filter(
        encryption, new CryptoPP::Redirector(cipher_queue), false, kTagSize_);
    plain_queue.TransferTo(filter);
    filter.MessageEnd();

    std::string cipher_text{};

    CryptoPP::StringSink store(cipher_text);

    cipher_queue.TransferTo(store);
    store.MessageEnd();

    std::cout << "hello" << cipher_text << '\n';

    cipher_bytes_out =
        minpass_crypto::CryptoppConversions::GetSecByteBlockFromString(
            cipher_text);

    // CryptoPP::StringSource(
    //     plain_, true,
    //     new CryptoPP::AuthenticatedEncryptionFilter(
    //         encryption, new CryptoPP::StringSink(cipher_text), false,
    //         kTagSize_));

  } catch (CryptoPP::InvalidArgument& e) {
    fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
  } catch (CryptoPP::Exception& e) {
    fmt::print("Caught Exception...\n{}\n\n", e.what());
  }

  return true;
}

auto AES_GCM_256::decrypt(const CryptoPP::SecByteBlock& cipher_bytes_in,
                          CryptoPP::SecByteBlock& plain_bytes_out) -> bool {
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
  //       cipher_text, true,
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

  return true;
}

}  // namespace minpass::minpass_crypto

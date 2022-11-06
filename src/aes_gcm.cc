// #include "utilities/aes_gcm.h"

// #include <cryptopp/aes.h>
// #include <cryptopp/cryptlib.h>
// #include <cryptopp/filters.h>
// #include <cryptopp/gcm.h>
// #include <cryptopp/hex.h>
// #include <fmt/core.h>

// #include <cassert>
// #include <string>

// #include "utilities/scrypt_kdf.h"

// namespace minpass::utilities {

// auto AES_GCM_256::encrypt(const std::string& plain_text,
//                           std::string& cipher_text) -> bool {
//   try {
//     fmt::print("plain text: {}\n", plain_text);
//     CryptoPP::GCM<CryptoPP::AES>::Encryption encryption;

//     ScryptKDF::GenerateKeyAndIV();

//     encryption.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
//     // e.SpecifyDataLengths( 0, plain_text.size(), 0 );

//     CryptoPP::StringSource(
//         plain_text, true,
//         new CryptoPP::AuthenticatedEncryptionFilter(
//             encryption, new CryptoPP::StringSink(cipher_text), false,
//             kTagSize_));

//   } catch (CryptoPP::InvalidArgument& e) {
//     fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
//   } catch (CryptoPP::Exception& e) {
//     fmt::print("Caught Exception...\n{}\n\n", e.what());
//   }

//   // Pretty print
//   std::string encoded;
//   encoded.clear();
//   {
//     CryptoPP::StringSource printer(
//         cipher_text, true,
//         new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
//   }
//   fmt::print("cipher text: {}\n", encoded);

//   return true;
// }

// auto AES_GCM_256::decrypt(const std::string& cipher_text,
//                           std::string& plain_text) -> bool {
//   try {
//     CryptoPP::GCM<CryptoPP::AES>::Decryption decryption;
//     decryption.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
//     // decryption.SpecifyDataLengths( 0, cipher_text.size()-kTagSize_, 0 );

//     CryptoPP::AuthenticatedDecryptionFilter df(
//         decryption, new CryptoPP::StringSink(plain_text),
//         CryptoPP::AuthenticatedDecryptionFilter::DEFAULT_FLAGS,
//         kTagSize_);  // AuthenticatedDecryptionFilter

//     // The StringSource dtor will be called immediately
//     //  after construction below. This will cause the
//     //  destruction of objects it owns. To stop the
//     //  behavior so we can get the decoding result from
//     //  the DecryptionFilter, we must use a redirector
//     //  or manually Put(...) into the filter without
//     //  using a StringSource.
//     CryptoPP::StringSource(
//         cipher_text, true,
//         new CryptoPP::Redirector(df /*, PASS_EVERYTHING */));  //
//         StringSource

//     // If the object does not throw, here's the only
//     //  opportunity to check the data's integrity
//     bool b = df.GetLastResult();
//     assert(true == b);

//     fmt::print("recovered text: {}\n", plain_text);

//   } catch (CryptoPP::HashVerificationFilter::HashVerificationFailed& e) {
//     fmt::print("Caught HashVerificationFailed...\n{}\n\n", e.what());
//   } catch (CryptoPP::InvalidArgument& e) {
//     fmt::print("Caught InvalidArgument...\n{}\n\n", e.what());
//   } catch (CryptoPP::Exception& e) {
//     fmt::print("Caught Exception...\n{}\n\n", e.what());
//   }

//   return true;
// }

// }  // namespace minpass::utilities

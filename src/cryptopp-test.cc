#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>  // for HexEncoder
#include <fmt/core.h>

#include <iostream>

#include "minpass_crypto.h"
#include "minpass_crypto/aes_gcm_256.h"
#include "minpass_crypto/crytopp_conversions.h"

auto main() -> int {
  auto xyz =
      minpass::minpass_crypto::CryptoppConversions::GetSecByteBlockFromString(
          "hell");
  const CryptoPP::StringSource key_out_constructor(
      xyz, xyz.size(), true,
      new CryptoPP::HexEncoder(new CryptoPP::FileSink(std::cout)));
  std::cout << minpass::minpass_crypto::CryptoppConversions::
                   GetStringFromSecByteBlock(xyz)
            << '\n';

  std::cout << minpass::MinpassCrypto::encrypt("hello") << '\n';

  // std::string plain_text("hello");
  // std::string cipher_text;
  // minpass::minpass_crypto::AES_GCM_256::encrypt(plain_text, cipher_text);

  // auto [key, salt, iv] =
  //     minpass::utilities::ScryptKDF::GenerateKeyAndIV(password_bytes);

  // std::string key_out;
  // std::string salt_out;
  // std::string iv_out;
  // {
  //   const CryptoPP::StringSource key_out_constructor(
  //       key, key.size(), true,
  //       new CryptoPP::HexEncoder(new CryptoPP::StringSink(key_out)));
  //   const CryptoPP::StringSource salt_out_constructor(
  //       salt, salt.size(), true,
  //       new CryptoPP::HexEncoder(new CryptoPP::StringSink(salt_out)));
  //   const CryptoPP::StringSource iv_out_constructor(
  //       iv, iv.size(), true,
  //       new CryptoPP::HexEncoder(new CryptoPP::StringSink(iv_out)));
  // }

  // fmt::print("\n\nout\n{}\n{}\n{}\n", key_out, salt_out, iv_out);
}

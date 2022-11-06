#include <cryptopp/filters.h>
#include <cryptopp/hex.h>  // for HexEncoder
#include <fmt/core.h>

#include "utilities/scrypt_kdf.h"

auto main() -> int {
  auto x = minpass::utilities::ScryptKDF::GetBytesFromString(
      std::string("Hello world"));

  for (auto &&i : x) {
    fmt::print("{} ", i);
  }
  fmt::print("\n");

  auto s = minpass::utilities::ScryptKDF::GetStringFromBytes(x);
  fmt::print("{}\n", s);

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

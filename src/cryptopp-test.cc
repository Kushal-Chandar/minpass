#include <cryptopp/filters.h>
#include <cryptopp/hex.h>  // for HexEncoder
#include <fmt/core.h>

#include "minpass_crypto/crytopp_conversions.h"

auto main() -> int {
  auto x = minpass::minpass_crypto::CryptoppConversions::GetBytesFromString(
      std::string("Hello world"));

  for (auto &&i : x) {
    fmt::print("{} ", i);
  }
  fmt::print("\n");

  auto s = minpass::minpass_crypto::CryptoppConversions::GetStringFromBytes(x);
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

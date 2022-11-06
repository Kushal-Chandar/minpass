#include "utilities/scrypt_kdf.h"

#include <cryptopp/config_int.h>  // for byte
#include <cryptopp/osrng.h>       // for AutoSeededRandomPool
#include <cryptopp/scrypt.h>      // for Scrypt
#include <cryptopp/secblock.h>    // for SecByteBlock, AllocatorBase::size_type

#include <iostream>
#include <tuple>   // for tuple
#include <vector>  // for vector

namespace minpass::utilities {

auto ScryptKDF::GenerateKeyAndIV(
    const std::vector<CryptoPP::byte>& password_bytes)
    -> std::tuple<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock,
                  CryptoPP::SecByteBlock> {
  CryptoPP::AutoSeededRandomPool prng;

  CryptoPP::SecByteBlock key(kKeySize_);
  CryptoPP::SecByteBlock initialization_vector(kIVSize_);
  CryptoPP::SecByteBlock salt(kSaltSize_);

  const CryptoPP::Scrypt scrypt;

  // DeriveKey
  // note: we need the new random salt for decryption
  prng.GenerateBlock(salt, salt.size());
  scrypt.DeriveKey(key, key.size(), password_bytes.data(),
                   password_bytes.size(), salt, salt.size(), kCost_,
                   kBlockSize_, kParallelization_);

  // DeriveIV
  prng.GenerateBlock(initialization_vector, initialization_vector.size());

  return {key, salt, initialization_vector};
}

auto ScryptKDF::GetStringFromBytes(const std::vector<CryptoPP::byte>& bytes_in)
    -> std::string {
  std::string string_out;
  std::transform(
      bytes_in.begin(), bytes_in.end(), std::back_inserter(string_out),
      [](char character) { return static_cast<CryptoPP::byte>(character); });
  return string_out;
}

auto ScryptKDF::GetBytesFromString(const std::string& string_in)
    -> std::vector<CryptoPP::byte> {
  std::vector<CryptoPP::byte> bytes_out(string_in.size());
  std::copy(string_in.begin(), string_in.end(), bytes_out.begin());
  return bytes_out;
}

}  // namespace minpass::utilities

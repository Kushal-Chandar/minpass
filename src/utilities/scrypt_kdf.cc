#include "utilities/scrypt_kdf.h"

#include <cryptopp/config_int.h>  // for byte
#include <cryptopp/files.h>       // for FileSink
#include <cryptopp/filters.h>     // for StringSource
#include <cryptopp/hex.h>         // for HexEncoder
#include <cryptopp/osrng.h>       // for AutoSeededRandomPool
#include <cryptopp/scrypt.h>      // for Scrypt
#include <cryptopp/secblock.h>    // for SecByteBlock

#include <algorithm>  // copy
#include <tuple>
#include <vector>  // for vector

namespace minpass::utilities {

auto ScryptKDF::GenerateKeyAndIV(const std::string& password)
    -> std::tuple<std::string, std::string> {
  CryptoPP::AutoSeededRandomPool prng;

  CryptoPP::SecByteBlock key(kKeySize_);
  CryptoPP::SecByteBlock initialization_vector(kIVSize_);
  CryptoPP::SecByteBlock salt(kSaltSize_);

  std::vector<CryptoPP::byte> password_bytes(password.size());
  std::copy(password.begin(), password.end(), password_bytes.begin());

  const CryptoPP::Scrypt scrypt;

  // DeriveKey
  prng.GenerateBlock(salt, salt.size());
  scrypt.DeriveKey(key, key.size(), password_bytes.data(),
                   password_bytes.size(), salt, salt.size(), kCost_,
                   kBlockSize_, kParallelization_);

  // DeriveIV
  prng.GenerateBlock(salt, salt.size());
  scrypt.DeriveKey(initialization_vector, initialization_vector.size(),
                   password_bytes.data(), password_bytes.size(), salt,
                   salt.size(), kCost_, kBlockSize_, kParallelization_);

  std::string key_out, iv_out;
  {
    const CryptoPP::StringSource key_out_constructor(
        key, key.size(), true,
        new CryptoPP::HexEncoder(new CryptoPP::StringSink(key_out)));
    const CryptoPP::StringSource iv_out_constructor(
        initialization_vector, initialization_vector.size(), true,
        new CryptoPP::HexEncoder(new CryptoPP::StringSink(iv_out)));
  }

  return {key_out, iv_out};
}

}  // namespace minpass::utilities

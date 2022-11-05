#include "utilities/scrypt_kdf.h"

#include <cryptopp/config_int.h>  // for byte
#include <cryptopp/hex.h>         // for HexEncoder
#include <cryptopp/osrng.h>       // for AutoSeededRandomPool
#include <cryptopp/scrypt.h>      // for Scrypt
#include <cryptopp/secblock.h>    // for SecByteBlock

#include <algorithm>  // copy
#include <tuple>
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

}  // namespace minpass::utilities

#include "utilities/scrypt_kdf.h"

#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/scrypt.h>
#include <cryptopp/secblock.h>

#include <vector>

namespace minpass::utilities {

auto ScryptKDF::GenerateKey(const std::string& password) -> void {
  CryptoPP::AutoSeededRandomPool prng;

  constexpr int kKeySize = 32;
  constexpr int kSaltSize = 8;
  constexpr int kCost = 1024;
  constexpr int kBlockSize = 8;
  constexpr int kParallelization = 16;

  CryptoPP::SecByteBlock key(kKeySize);
  CryptoPP::SecByteBlock salt(kSaltSize);

  std::vector<CryptoPP::byte> password_bytes(password.size());
  std::copy(password.begin(), password.end(), password_bytes.begin());

  prng.GenerateBlock(key, key.size());
  prng.GenerateBlock(salt, salt.size());

  const CryptoPP::Scrypt scrypt;

  scrypt.DeriveKey(key, key.size(), password_bytes.data(),
                   password_bytes.size(), salt, salt.size(), kCost, kBlockSize,
                   kParallelization);

  std::cout << "Key: ";

  {
    const CryptoPP::StringSource temp(
        key, key.size(), true,
        new CryptoPP::HexEncoder(new CryptoPP::FileSink(std::cout)));
  }

  std::cout << "..." << std::endl;
}

}  // namespace minpass::utilities

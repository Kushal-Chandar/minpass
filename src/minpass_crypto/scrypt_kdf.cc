#include "minpass_crypto/scrypt_kdf.h"

#include <cryptopp/config_int.h>  // for byte
#include <cryptopp/osrng.h>       // for AutoSeededRandomPool
#include <cryptopp/scrypt.h>      // for Scrypt
#include <cryptopp/secblock.h>    // for SecByteBlock, AllocatorBase::size_type

#include <string>
#include <tuple>  // for tuple

#include "minpass_crypto/crytopp_conversions.h"

namespace minpass::minpass_crypto {

auto ScryptKDF::GetEncryptionKeySaltIV(
    const CryptoPP::SecByteBlock& password_bytes)
    -> std::tuple<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock,
                  CryptoPP::SecByteBlock> {
  CryptoPP::AutoSeededRandomPool prng;

  CryptoPP::SecByteBlock key(kKeySize_);
  CryptoPP::SecByteBlock initialization_vector(kIVSize_);
  CryptoPP::SecByteBlock salt(kSaltSize_);

  const CryptoPP::Scrypt scrypt;

  // DeriveKey
  // note: we need the same salt for decryption
  prng.GenerateBlock(salt, salt.size());
  scrypt.DeriveKey(key, key.size(), password_bytes, password_bytes.size(), salt,
                   salt.size(), kCost_, kBlockSize_, kParallelization_);

  // DeriveIV
  prng.GenerateBlock(initialization_vector, initialization_vector.size());

  return {key, salt, initialization_vector};
}

auto ScryptKDF::GetDecryptionKey(const CryptoPP::SecByteBlock& password_bytes,
                                 const CryptoPP::SecByteBlock& salt)
    -> CryptoPP::SecByteBlock {
  CryptoPP::SecByteBlock key(kKeySize_);
  const CryptoPP::Scrypt scrypt;
  // DeriveKey
  scrypt.DeriveKey(key, key.size(), password_bytes, password_bytes.size(), salt,
                   salt.size(), kCost_, kBlockSize_, kParallelization_);
  return key;
}

auto ScryptKDF::AddSaltAndIVToCipher(
    CryptoPP::SecByteBlock& salt, CryptoPP::SecByteBlock& initialization_vector,
    std::string& cipher_text) -> void {
  cipher_text += CryptoppConversions::GetStringFromSecByteBlock(
      salt + initialization_vector);
}

auto ScryptKDF::SeperateSaltAndIVFromCipher(
    const std::string& cipher_text_with_salt_and_iv)
    -> std::tuple<CryptoPP::SecByteBlock, CryptoPP::SecByteBlock> {
  auto initialization_vector = CryptoppConversions::GetSecByteBlockFromString(
      cipher_text_with_salt_and_iv.cend() - kIVSize_,
      cipher_text_with_salt_and_iv.cend());

  auto salt = CryptoppConversions::GetSecByteBlockFromString(
      cipher_text_with_salt_and_iv.cend() - kIVSize_ - kSaltSize_,
      cipher_text_with_salt_and_iv.cend() - kIVSize_);
  return {salt, initialization_vector};
}

}  // namespace minpass::minpass_crypto

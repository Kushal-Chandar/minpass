#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>  // for HexEncoder
#include <fmt/core.h>

#include <iostream>

#include "minpass_crypto.h"
#include "minpass_crypto/aes_gcm_256.h"
#include "minpass_crypto/crytopp_conversions.h"

auto main() -> int {
  std::unique_ptr<minpass::MinpassCrypto> ptr =
      std::make_unique<minpass::minpass_crypto::AES_GCM_256>("password");

  auto enc = ptr->Encrypt("This is a very very very secret password");

  std::cout << "Encrypt Result: " << enc << '\n';
  std::cout << "Dncrypt Result: " << ptr->Decrypt(enc) << '\n';
}

// #include "minpass_crypto/crytopp_conversions.h"

// #include <cryptopp/config_int.h>  // for byte
// #include <cryptopp/osrng.h>       // for AutoSeededRandomPool
// #include <cryptopp/scrypt.h>      // for Scrypt
// #include <cryptopp/secblock.h>    // for SecByteBlock,
// AllocatorBase::size_type

// #include <tuple>  // for tuple

// namespace minpass::minpass_crypto {

// auto CryptoppConversions::GetStringFromSecByteBlock(
//     const CryptoPP::SecByteBlock& bytes_in) -> std::string {
//   std::string string_out;
//   std::transform(
//       bytes_in.begin(), bytes_in.end(), std::back_inserter(string_out),
//       [](char character) { return static_cast<CryptoPP::byte>(character); });
//   return string_out;
// }

// auto CryptoppConversions::GetSecByteBlockFromString(
//     const std::string& string_in) -> CryptoPP::SecByteBlock {
//   CryptoPP::SecByteBlock bytes_out(string_in.size());
//   std::copy(string_in.begin(), string_in.end(), bytes_out.begin());
//   return bytes_out;
// }

// auto CryptoppConversions::GetSecByteBlockFromString(
//     std::string::const_iterator begin, std::string::const_iterator end)
//     -> CryptoPP::SecByteBlock {
//   CryptoPP::SecByteBlock bytes_out(
//       static_cast<size_t>(std::distance(begin, end)));
//   std::copy(begin, end, bytes_out.begin());
//   return bytes_out;
// }

// }  // namespace minpass::minpass_crypto

#include "minpass_crypto/crytopp_conversions.h"

#include <drogon/drogon_test.h>

#include "test_utilities/random_string_generator.h"

const int kRandomStringLen = 30;

DROGON_TEST(MinpassCryptoppConversions_StringAndSecByteBlock_Overload1) {
  // Testing:
  // Back and forth conversion between GetSecByteBlockFromString_Overload1 (pass
  // in string) and GetStringFromSecByteBlock

  auto random_string = minpass::tests::generate_random_string(kRandomStringLen);
  auto random_string_bytes =
      minpass::minpass_crypto::CryptoppConversions::GetSecByteBlockFromString(
          random_string);

  auto random_string_recovered =
      minpass::minpass_crypto::CryptoppConversions::GetStringFromSecByteBlock(
          random_string_bytes);

  CHECK(random_string == random_string_recovered);
}

DROGON_TEST(MinpassCryptoppConversions_StringAndSecByteBlock_Overload2) {
  // Back and forth conversion between GetSecByteBlockFromString_Overload2 (pass
  // in from and back iterators) and GetStringFromSecByteBlock

  auto random_string = minpass::tests::generate_random_string(kRandomStringLen);
  auto random_string_bytes =
      minpass::minpass_crypto::CryptoppConversions::GetSecByteBlockFromString(
          random_string.begin() + 1, random_string.end() - 3);

  auto random_string_recovered =
      minpass::minpass_crypto::CryptoppConversions::GetStringFromSecByteBlock(
          random_string_bytes);

  std::string const substring(random_string.begin() + 1,
                              random_string.end() - 3);

  CHECK(substring == random_string_recovered);
}

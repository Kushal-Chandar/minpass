#include "utilities/aes_gcm.h"

#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/gcm.h>
#include <cryptopp/hex.h>

#include <cassert>
#include <string>

namespace minpass::utilities {
auto AES_GCM_256::encrypt(const std::string& plain_text,
                          std::string& cipher_text) -> bool {
  try {
    cout << "plain text: " << plain_text << endl;

    CryptoPP::GCM<CryptoPP::AES>::Encryption e;

    e.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
    // e.SpecifyDataLengths( 0, plain_text.size(), 0 );

    CryptoPP::StringSource(plain_text, true,
                           new CryptoPP::AuthenticatedEncryptionFilter(
                               e, new CryptoPP::StringSink(cipher_text), false,
                               kTagSize_)  // AuthenticatedEncryptionFilter
    );                                     // StringSource
  } catch (CryptoPP::InvalidArgument& e) {
    cerr << "Caught InvalidArgument..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  } catch (CryptoPP::Exception& e) {
    cerr << "Caught Exception..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  }

  // Pretty print
  std::string encoded;
  encoded.clear();
  {
    const CryptoPP::StringSource printer(
        cipher_text, true,
        new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
  }
  cout << "cipher_text text: " << encoded << endl;

  return true;
}

auto AES_GCM_256::decrypt(const std::string& cipher_text,
                          std::string& plain_text) -> bool {
  try {
    CryptoPP::GCM<CryptoPP::AES>::Decryption d;
    d.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
    // d.SpecifyDataLengths( 0, cipher_text.size()-kTagSize_, 0 );

    CryptoPP::AuthenticatedDecryptionFilter df(
        d, new CryptoPP::StringSink(plain_text),
        CryptoPP::AuthenticatedDecryptionFilter::DEFAULT_FLAGS,
        kTagSize_);  // AuthenticatedDecryptionFilter

    // The StringSource dtor will be called immediately
    //  after construction below. This will cause the
    //  destruction of objects it owns. To stop the
    //  behavior so we can get the decoding result from
    //  the DecryptionFilter, we must use a redirector
    //  or manually Put(...) into the filter without
    //  using a StringSource.
    StringSource(cipher_text, true,
                 new Redirector(df /*, PASS_EVERYTHING */));  // StringSource

    // If the object does not throw, here's the only
    //  opportunity to check the data's integrity
    bool b = df.GetLastResult();
    assert(true == b);

    cout << "recovered text: " << plain_text << endl;
  } catch (CryptoPP::HashVerificationFilter::HashVerificationFailed& e) {
    cerr << "Caught HashVerificationFailed..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  } catch (CryptoPP::InvalidArgument& e) {
    cerr << "Caught InvalidArgument..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  } catch (CryptoPP::Exception& e) {
    cerr << "Caught Exception..." << endl;
    cerr << e.what() << endl;
    cerr << endl;
  }

  return true;
}

}  // namespace minpass::utilities

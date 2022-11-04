#if !defined(OPENSSL_GCM)
#define OPENSSL_GCM

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>

#include <cstring>

namespace minpass::utilities {

class OpenSSLGCM {
 public:
  int gcm_encrypt(unsigned char *plaintext, int plaintext_len,
                  unsigned char *aad, int aad_len, unsigned char *key,
                  unsigned char *iv, int iv_len, unsigned char *ciphertext,
                  unsigned char *tag);

  int gcm_decrypt(unsigned char *ciphertext, int ciphertext_len,
                  unsigned char *aad, int aad_len, unsigned char *tag,
                  unsigned char *key, unsigned char *iv, int iv_len,
                  unsigned char *plaintext);

  int calling(void);

 private:
  void handleErrors(void);
};

}  // namespace minpass::utilities

#endif  // OPENSSL_GCM

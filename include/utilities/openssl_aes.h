#if !defined(OPENSSL_AES)
#define OPENSSL_AES

// #include <openssl/conf.h>
// #include <openssl/err.h>
// #include <openssl/evp.h>
// #include <string.h>

// int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char
// *key,
//             unsigned char *iv, unsigned char *plaintext) {
//   EVP_CIPHER_CTX *ctx;

//   int len;

//   int plaintext_len;

//   /* Create and initialise the context */
//   if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

//   /*
//    * Initialise the decryption operation. IMPORTANT - ensure you use a key
//    * and IV size appropriate for your cipher
//    * In this example we are using 256 bit AES (i.e. a 256 bit key). The
//    * IV size for *most* modes is the same as the block size. For AES this
//    * is 128 bits
//    */
//   if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
//     handleErrors();

//   /*
//    * Provide the message to be decrypted, and obtain the plaintext output.
//    * EVP_DecryptUpdate can be called multiple times if necessary.
//    */
//   if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext,
//   ciphertext_len))
//     handleErrors();
//   plaintext_len = len;

//   /*
//    * Finalise the decryption. Further plaintext bytes may be written at
//    * this stage.
//    */
//   if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
//   plaintext_len += len;

//   /* Clean up */
//   EVP_CIPHER_CTX_free(ctx);

//   return plaintext_len;
// }

// int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
//             unsigned char *iv, unsigned char *ciphertext) {
//   EVP_CIPHER_CTX *ctx;

//   int len;

//   int ciphertext_len;

//   /* Create and initialise the context */
//   if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

//   /*
//    * Initialise the encryption operation. IMPORTANT - ensure you use a key
//    * and IV size appropriate for your cipher
//    * In this example we are using 256 bit AES (i.e. a 256 bit key). The
//    * IV size for *most* modes is the same as the block size. For AES this
//    * is 128 bits
//    */
//   if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
//     handleErrors();

//   /*
//    * Provide the message to be encrypted, and obtain the encrypted output.
//    * EVP_EncryptUpdate can be called multiple times if necessary
//    */
//   if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext,
//   plaintext_len))
//     handleErrors();
//   ciphertext_len = len;

//   /*
//    * Finalise the encryption. Further ciphertext bytes may be written at
//    * this stage.
//    */
//   if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
//   ciphertext_len += len;

//   /* Clean up */
//   EVP_CIPHER_CTX_free(ctx);

//   return ciphertext_len;
// }

// void call_me() {
//   /*
//    * Set up the key and iv. Do I need to say to not hard code these in a
//    * real application? :-)
//    */

//   /* A 256 bit key */
//   unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

//   /* A 128 bit IV */
//   unsigned char *iv = (unsigned char *)"0123456789012345";

//   /* Message to be encrypted */
//   unsigned char *plaintext =
//       (unsigned char *)"The quick brown fox jumps over the lazy dog";

//   /*
//    * Buffer for ciphertext. Ensure the buffer is long enough for the
//    * ciphertext which may be longer than the plaintext, depending on the
//    * algorithm and mode.
//    */
//   unsigned char ciphertext[128];

//   /* Buffer for the decrypted text */
//   unsigned char decryptedtext[128];

//   int decryptedtext_len, ciphertext_len;

//   /* Encrypt the plaintext */
//   ciphertext_len =
//       encrypt(plaintext, strlen((char *)plaintext), key, iv, ciphertext);

//   /* Do something useful with the ciphertext here */
//   printf("Ciphertext is:\n");
//   BIO_dump_fp(stdout, (const char *)ciphertext, ciphertext_len);

//   /* Decrypt the ciphertext */
//   decryptedtext_len =
//       decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

//   /* Add a NULL terminator. We are expecting printable text */
//   decryptedtext[decryptedtext_len] = '\0';

//   /* Show the decrypted text */
//   printf("Decrypted text is:\n");
//   printf("%s\n", decryptedtext);
// }

// typedef unsigned char byte;
// typedef std::basic_string<char, std::char_traits<char>, zallocator<char> >
//     secure_string;
// using EVP_CIPHER_CTX_ptr =
//     std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

// void aes_encrypt(const byte key[KEY_SIZE], const byte iv[BLOCK_SIZE],
//                  const secure_string &ptext, secure_string &ctext) {
//   EVP_CIPHER_CTX_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
//   int rc = EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
//   if (rc != 1) throw std::runtime_error("EVP_EncryptInit_ex failed");

//   // Cipher text expands upto BLOCK_SIZE
//   ctext.resize(ptext.size() + BLOCK_SIZE);
//   int out_len1 = (int)ctext.size();

//   rc = EVP_EncryptUpdate(ctx.get(), (byte *)&ctext[0], &out_len1,
//                          (const byte *)&ptext[0], (int)ptext.size());
//   if (rc != 1) throw std::runtime_error("EVP_EncryptUpdate failed");

//   int out_len2 = (int)ctext.size() - out_len1;
//   rc = EVP_EncryptFinal_ex(ctx.get(), (byte *)&ctext[0] + out_len1,
//   &out_len2); if (rc != 1) throw std::runtime_error("EVP_EncryptFinal_ex
//   failed");

//   // Set cipher text size now that we know it
//   ctext.resize(out_len1 + out_len2);
// }

// auto call() -> void {
//   // Load the necessary cipher
//   EVP_add_cipher(EVP_aes_256_cbc());

//   // plaintext, ciphertext, recovered text
//   secure_string ptext = "Yoda said, Do or do not. There is no try.";
//   secure_string ctext, rtext;

//   byte key[KEY_SIZE], iv[BLOCK_SIZE];
//   gen_params(key, iv);

//   aes_encrypt(key, iv, ptext, ctext);
//   aes_decrypt(key, iv, ctext, rtext);

//   OPENSSL_cleanse(key, KEY_SIZE);
//   OPENSSL_cleanse(iv, BLOCK_SIZE);

//   std::cout << "Original message:\n" << ptext << std::endl;
//   std::cout << "Recovered message:\n" << rtext << std::endl;

//   return 0;
// }

#endif  // OPENSSL_AES

#####################################################
### Source files in IMPL/crypto
#####################################################

#####################################################
### adding sources
#####################################################
target_sources(crypto PRIVATE aes_gcm_256.cc crytopp_conversions.cc
                              scrypt_kdf.cc)

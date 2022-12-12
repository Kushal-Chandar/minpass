#####################################################
### Source files in INC/minpass_crypto
#####################################################

#####################################################
### adding sources
#####################################################
target_sources(sqlite3_client PRIVATE aes_gcm_256.h crytopp_conversions.h
                                      scrypt_kdf.h)

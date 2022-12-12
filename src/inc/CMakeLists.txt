#####################################################
### Source files in INC
#####################################################

#####################################################
### adding sources
#####################################################
target_sources(utilities PRIVATE)
target_sources(minpass_crypto PRIVATE minpass_crypto.h)
target_sources(minpass_types PRIVATE minpass_types.h)
target_sources(sqlite3_client PRIVATE sqlite3_client.h)
target_sources(minpass PRIVATE)

#####################################################
### Source files in other subdirectories
#####################################################
add_subdirectory(minpass_crypto)
add_subdirectory(sqlite3_client)
add_subdirectory(utilities)

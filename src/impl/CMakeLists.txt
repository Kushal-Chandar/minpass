#####################################################
### Source files in IMPL
#####################################################

#####################################################
### adding sources
#####################################################
target_sources(utilities PRIVATE)
target_sources(minpass_crypto PRIVATE minpass_crypto.cc)
target_sources(minpass_types PRIVATE minpass_types.cc)
target_sources(sqlite3_client PRIVATE sqlite3_client.cc)
target_sources(minpass PRIVATE main.cc)

#####################################################
### Source files in other subdirectories
#####################################################
add_subdirectory(minpass_crypto)
add_subdirectory(sqlite3_client)
add_subdirectory(utilities)

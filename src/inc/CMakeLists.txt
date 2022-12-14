#####################################################
### Source files in INC
#####################################################

#####################################################
### adding sources
#####################################################
target_sources(utilities PRIVATE)
target_sources(crypto PRIVATE crypto.h)
target_sources(types PRIVATE types.h)
target_sources(cli PRIVATE cli.h)
target_sources(sqlite3_client PRIVATE sqlite3_client.h)
target_sources(minpass PRIVATE)

#####################################################
### Source files in other subdirectories
#####################################################
add_subdirectory(crypto)
add_subdirectory(sqlite3_client)
add_subdirectory(utilities)

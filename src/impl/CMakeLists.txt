#####################################################
### Source files in IMPL
#####################################################

#####################################################
### adding sources
#####################################################
target_sources(utilities PRIVATE)
target_sources(crypto PRIVATE crypto.cc)
target_sources(types PRIVATE types.cc)
target_sources(cli PRIVATE cli.cc)
target_sources(sqlite3_client PRIVATE sqlite3_client.cc)
target_sources(minpass PRIVATE main.cc)

#####################################################
### Source files in other subdirectories
#####################################################
add_subdirectory(crypto)
add_subdirectory(sqlite3_client)
add_subdirectory(utilities)

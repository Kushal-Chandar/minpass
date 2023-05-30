#####################################################
### Source files in IMPL/sqlite3_client
#####################################################

#####################################################
### adding sources
#####################################################
target_sources(sqlite3_client PRIVATE helpers.cc #[[ request_processor.cc ]]
                                      json_processor.cc)

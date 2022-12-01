include_guard()

# ----------------------------------------------------------------------------
#   Configure file
# ----------------------------------------------------------------------------
configure_file(
  ${PROJECT_SOURCE_DIR}/src/configuration/config.h.ini
  ${PROJECT_SOURCE_DIR}/src/configuration/config.h
  ESCAPE_QUOTES
  @ONLY)

# ----------------------------------------------------------------------------
#   A lib that has private and public headers
# ----------------------------------------------------------------------------
add_library(configuration_header STATIC)
set_target_properties(configuration_header PROPERTIES LINKER_LANGUAGE CXX)
target_sources(configuration_header
               PRIVATE ${PROJECT_SOURCE_DIR}/src/configuration/config.h)

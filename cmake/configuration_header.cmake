include_guard()

set(${PROJECT_NAME_UPPER}_CONFIG_DIR ${${PROJECT_NAME_UPPER}_SOURCE_DIR}/config)
# ----------------------------------------------------------------------------
#   Configure file
# ----------------------------------------------------------------------------
configure_file(
  ${${PROJECT_NAME_UPPER}_CONFIG_DIR}/config.h.ini
  ${${PROJECT_NAME_UPPER}_CONFIG_DIR}/config.h
  ESCAPE_QUOTES
  @ONLY)

# ----------------------------------------------------------------------------
#   An interface library that provides configuration info
#   (to any target that links to it), without producing a file
# ----------------------------------------------------------------------------
add_library(configuration_header INTERFACE)
set_target_properties(configuration_header PROPERTIES LINKER_LANGUAGE CXX)
target_sources(configuration_header
               INTERFACE ${${PROJECT_NAME_UPPER}_CONFIG_DIR}/config.h)
target_include_directories(configuration_header
                           INTERFACE ${${PROJECT_NAME_UPPER}_CONFIG_DIR})

unset(${${PROJECT_NAME_UPPER}_CONFIG_DIR})

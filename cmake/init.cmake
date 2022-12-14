include_guard()

option(INSTALL_OR_UPDATE_VCPKG
       "Install or update vcpkg in the project root directory" OFF)
option(ENABLE_VCPKG "Enable package management with vcpkg" OFF)
option(MANIFEST_FEATURE_TEST "Get packages required for testing" OFF)
option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
option(CODE_COVERAGE "Enable coverage reporting" OFF)
option(BUILD_TESTING "Build the testing tree" OFF)
option(DOCKER_BUILD "Build for docker image" OFF)
option(ENABLE_AUTOMATIC_VERSIONING
       "Generate project version from git annotated tags" OFF)
option(ENABLE_CUSTOM_VARIABLES "Creates custom variables with project name" OFF)
option(ENABLE_CONFIGURATION_HEADER
       "Generate a header file with project details" OFF)
option(ENABLE_DOXYGEN "Build doxygen docs" OFF)
option(ENABLE_CCACHE "Enable ccache for faster compilation" OFF)
option(ENABLE_IPO "Enable IPO/LTO, for improved runtime performance" OFF)
option(SANITIZE_ADDRESS "Enable sanitizer for address" OFF)
option(SANITIZE_UNDEFINED "Enable sanitizer for undefined behaviour" OFF)

# ----------------------------------------------------------------------------
#   Get all options set from options.cmake
# ----------------------------------------------------------------------------
include(${CMAKE_CURRENT_SOURCE_DIR}/options.cmake)

# ----------------------------------------------------------------------------
#   Setting output directories for all targets
# ----------------------------------------------------------------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)

# ----------------------------------------------------------------------------
#   Replace "-" with "_" in project name and get upper and lower case name
# ----------------------------------------------------------------------------
string(
  REGEX
  REPLACE "-"
          "_"
          PROJECT_NAME_NO_HYPEN
          ${PROJECT_NAME})
string(TOLOWER ${PROJECT_NAME_NO_HYPEN} PROJECT_NAME_LOWER)
string(TOUPPER ${PROJECT_NAME_NO_HYPEN} PROJECT_NAME_UPPER)
unset(PROJECT_NAME_NO_HYPEN)

# ----------------------------------------------------------------------------
#   Detecting linux
# ----------------------------------------------------------------------------
if(UNIX AND NOT APPLE)
  set(LINUX TRUE)
endif()

# ----------------------------------------------------------------------------
#   An interface library containing all compile options
# ----------------------------------------------------------------------------
add_library(project_compile_options INTERFACE)

# ----------------------------------------------------------------------------
#   Prevent building in source directory
# ----------------------------------------------------------------------------
# get absolute path with symlinks resolved
file(REAL_PATH "${CMAKE_CURRENT_BINARY_DIR}" BINARY_DIR)
file(REAL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" SOURCE_DIR)
if("${SOURCE_DIR}" STREQUAL "${BINARY_DIR}")
  message("# ---------------------------------------------------------")
  message("#   Warning: build directory and source directory are same.")
  message("# ---------------------------------------------------------")
  message(FATAL_ERROR "In source build.")
endif()
# unset previous variables
unset(BINARY_DIR)
unset(SOURCE_DIR)

# ----------------------------------------------------------------------------
#   Project configuration
# ----------------------------------------------------------------------------
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ----------------------------------------------------------------------------
#   Link time optimizations
# ----------------------------------------------------------------------------
if(ENABLE_IPO AND (CMAKE_BUILD_TYPE STREQUAL "Release"
                   OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo"))
  include(CheckIPOSupported)
  check_ipo_supported(RESULT result OUTPUT output)
  if(result)
    message(STATUS "IPO is supported")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
  else()
    message(STATUS "IPO is not supported: ${output}")
  endif()
endif()

# ----------------------------------------------------------------------------
#   Use -std=c++20 instead of -std=gnu++20 (Disable gnu specific features)
# ----------------------------------------------------------------------------
set(CMAKE_CXX_EXTENSIONS OFF)

# ----------------------------------------------------------------------------
#   Call other scripts from current directory
# ----------------------------------------------------------------------------
if(ENABLE_CCACHE)
  include(${CMAKE_CURRENT_LIST_DIR}/ccache.cmake)
endif()
if(ENABLE_CUSTOM_VARIABLES)
  include(${CMAKE_CURRENT_LIST_DIR}/custom_variables.cmake)
endif()
include(${CMAKE_CURRENT_LIST_DIR}/graphviz.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/compiler_warnings.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/sanitizers.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/static_analysis.cmake)
if(ENABLE_AUTOMATIC_VERSIONING)
  include(${CMAKE_CURRENT_LIST_DIR}/git_tag_versioning.cmake)
endif()
if(ENABLE_CONFIGURATION_HEADER)
  include(${CMAKE_CURRENT_LIST_DIR}/configuration_header.cmake)
endif()
if(ENABLE_VCPKG)
  include(${CMAKE_CURRENT_LIST_DIR}/vcpkg.cmake)
endif()
if(BUILD_TESTING)
  include(${CMAKE_CURRENT_LIST_DIR}/testing.cmake)
endif()
if(ENABLE_DOXYGEN)
  include(${CMAKE_CURRENT_LIST_DIR}/doxygen.cmake)
endif()

include_guard()
# ----------------------------------------------------------------------------
#   Set vcpkg location
# ----------------------------------------------------------------------------
set(VCPKG_PARENT_DIR ${CMAKE_SOURCE_DIR}/tools)
set(VCPKG_DIR ${VCPKG_PARENT_DIR}/vcpkg)

# ----------------------------------------------------------------------------
#   Install or update vcpkg and all dependencies
# ----------------------------------------------------------------------------
function(install_or_update_vcpkg)
  find_program(GIT_EXECUTABLE "git" REQUIRED)
  file(MAKE_DIRECTORY ${VCPKG_PARENT_DIR})
  if(WIN32 AND "${CMAKE_EXECUTABLE_SUFFIX}" STREQUAL "")
    set(CMAKE_EXECUTABLE_SUFFIX ".exe")
  endif()

  if(EXISTS ${VCPKG_DIR} AND EXISTS
                             ${VCPKG_DIR}/vcpkg${CMAKE_EXECUTABLE_SUFFIX})
    message("Updating vcpkg\n")
    execute_process(COMMAND "${GIT_EXECUTABLE}" "pull"
                    WORKING_DIRECTORY "${VCPKG_DIR}")
  else()
    execute_process(
      COMMAND "${GIT_EXECUTABLE}" "clone"
              "https://github.com/microsoft/vcpkg.git"
      WORKING_DIRECTORY "${VCPKG_PARENT_DIR}" COMMAND_ERROR_IS_FATAL LAST)
  endif()

  if(WIN32)
    execute_process(
      COMMAND "bootstrap-vcpkg.bat" "-disableMetrics"
      WORKING_DIRECTORY "${VCPKG_DIR}" COMMAND_ERROR_IS_FATAL LAST)
  else()
    execute_process(
      COMMAND "./bootstrap-vcpkg.sh" "-disableMetrics"
      WORKING_DIRECTORY "${VCPKG_DIR}" COMMAND_ERROR_IS_FATAL LAST)
  endif()
endfunction()

# ----------------------------------------------------------------------------
#   Update or install vcpkg based on option
# ----------------------------------------------------------------------------
if(UPDATE_VCPKG)
  install_or_update_vcpkg()
endif()

# ----------------------------------------------------------------------------
#   Get packages required for testing
# ----------------------------------------------------------------------------
if(BUILD_TESTING)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

if(BUILD_SHARED_LIBS)
  set(MINGW_LINKING "dynamic")
else()
  set(MINGW_LINKING "static")
endif()

set(VCPKG_CMAKE_SYSTEM_NAME
    "MinGW"
    CACHE STRING "")
set(VCPKG_TARGET_IS_MINGW
    TRUE
    CACHE STRING "")

set(VCPKG_TARGET_TRIPLET "x64-mingw-${MINGW_LINKING}")
set(VCPKG_HOST_TRIPLET "x64-mingw-${MINGW_LINKING}")
include(${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)

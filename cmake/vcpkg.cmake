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

  if(EXISTS ${VCPKG_DIR} AND EXISTS ${VCPKG_DIR}/.git/)
    message("Updating vcpkg\n")
    execute_process(COMMAND "${GIT_EXECUTABLE}" "pull"
                    WORKING_DIRECTORY "${VCPKG_DIR}")
  else()
    if(EXISTS ${VCPKG_DIR})
      file(REMOVE_RECURSE ${VCPKG_DIR})
    endif()
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
  message("You can turn this OFF in options.cmake\n")
endfunction()

# ----------------------------------------------------------------------------
#   Update or install vcpkg based on option
# ----------------------------------------------------------------------------
if(INSTALL_OR_UPDATE_VCPKG)
  install_or_update_vcpkg()
endif()

# ----------------------------------------------------------------------------
#   Get packages required for testing
# ----------------------------------------------------------------------------
# if(BUILD_TESTING)
#   list(APPEND VCPKG_MANIFEST_FEATURES "tests")
# endif()
# Not requried as drogon tests are a part of drogon package and cannot be seperated

# ----------------------------------------------------------------------------
#   VCPKG configuration
# ----------------------------------------------------------------------------
set(LINKING "")
if(BUILD_SHARED_LIBS)
  set(LINKING "-dynamic")
else()
  set(LINKING "-static")
endif()

set(PLATFORM "")

if(LINUX)
  set(VCPKG_CMAKE_SYSTEM_NAME
      "UNIX"
      CACHE STRING "")
  set(VCPKG_TARGET_IS_MINGW
      FALSE
      CACHE STRING "")
  message(STATUS "Running on Linux")
  set(PLATFORM "-linux")
  if(NOT BUILD_SHARED_LIBS)
    set(LINKING "")
  endif(NOT BUILD_SHARED_LIBS)
endif(LINUX)

if(WIN32) # only supporting mingw
  set(VCPKG_CMAKE_SYSTEM_NAME
      "MinGW"
      CACHE STRING "")
  set(VCPKG_TARGET_IS_MINGW
      TRUE
      CACHE STRING "")
  message(STATUS "Running on windows")
  set(PLATFORM "-mingw")
endif(WIN32)

set(VCPKG_TARGET_TRIPLET "x64${PLATFORM}${LINKING}")
set(VCPKG_HOST_TRIPLET "x64${PLATFORM}${LINKING}")
message(
  NOTICE
  "\nIf you are getting an error here, please turn ON INSTALL_OR_UPDATE_VCPKG option or you can replace the below path with your vcpkg toolchain's absolute path.\n"
)
include(${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake)

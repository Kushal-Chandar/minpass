include_guard()

# ----------------------------------------------------------------------------
#   Uncomment to set options or set options in cmake-gui.
# ----------------------------------------------------------------------------
set(DOCKER_BUILD ON)
# set(BUILD_SHARED_LIBS ON)
set(INSTALL_OR_UPDATE_VCPKG ON) # turn this off for docker
# set(WARNINGS_AS_ERRORS ON)
# set(CODE_COVERAGE ON) # enable in github actions
set(BUILD_TESTING ON)
# set(ENABLE_DOXYGEN ON) # turn this off for docker

set(ENABLE_CCACHE ON)
# set(ENABLE_IPO ON)

# ----------------------------------------------------------------------------
#   Enable sanitizer checks (only on at a time)
# ----------------------------------------------------------------------------
# set(SANITIZE_ADDRESS ON)
# set(SANITIZE_UNDEFINED ON)

if(DOCKER_BUILD)
  set(ENABLE_DOXYGEN OFF) # turn this off for docker
  set(INSTALL_OR_UPDATE_VCPKG OFF)
  # turn this off for docker unless needed for a testing framework that you cannot find on ubuntu
endif()

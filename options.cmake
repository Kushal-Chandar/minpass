include_guard()

# ----------------------------------------------------------------------------
#   Uncomment to set options or set options in cmake-gui.
# ----------------------------------------------------------------------------
# set(DOCKER_BUILD ON)
# set(BUILD_SHARED_LIBS ON)
set(ENABLE_VCPKG ON) # turn this off for docker
# set(INSTALL_OR_UPDATE_VCPKG ON)
# set(WARNINGS_AS_ERRORS ON)
# set(CODE_COVERAGE ON) # enable in github actions
set(BUILD_TESTING ON)
set(ENABLE_DOXYGEN ON) # turn this off for docker

set(ENABLE_CCACHE ON)
# set(ENABLE_IPO ON)

# ----------------------------------------------------------------------------
#   Enable sanitizer checks (only on at a time)
# ----------------------------------------------------------------------------
# set(SANITIZE_ADDRESS ON)
# set(SANITIZE_UNDEFINED ON)

# ----------------------------------------------------------------------------
#   Docker configuration
# ----------------------------------------------------------------------------
if(DOCKER_BUILD)
  set(ENABLE_DOXYGEN OFF)
  # turn this off for docker we are not building docks for prod
  set(ENABLE_VCPKG OFF)
  # turn this off for docker unless you are testing and your testing framework not available in docker image
  set(BUILD_TESTING OFF)
  # turn this off for docker unless your want your tests to run in docker before deployment
endif()

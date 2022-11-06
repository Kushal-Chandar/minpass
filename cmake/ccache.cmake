include_guard()

if(ENABLE_CCACHE)
  find_program(CACHE_BINARY NAMES "ccache")
  if(CACHE_BINARY)
    message(STATUS "ccache was found.")
    set(CMAKE_CXX_COMPILER_LAUNCHER
        ${CACHE_BINARY}
        CACHE STRING "")
  else()
    message(STATUS "ccache was not found.")
  endif()
endif()

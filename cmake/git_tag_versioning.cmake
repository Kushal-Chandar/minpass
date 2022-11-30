include_guard()

function(get_latest_annotated_tag)
  message(${CMAKE_SOURCE_DIR})
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --abbrev=0 --match "v*"
    WORKING_DIRECTORY "${PROJEC_SOURCE_DIR}"
    OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
    RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(NOT GIT_DESCRIBE_ERROR_CODE)
    set(PROJ_VER
        ${GIT_DESCRIBE_VERSION}
        PARENT_SCOPE)
    message(STATUS "PROJECT VERSION: " ${GIT_DESCRIBE_VERSION})
    execute_process(
      COMMAND ${GIT_EXECUTABLE} rev-list -n 1 ${GIT_DESCRIBE_VERSION}
      WORKING_DIRECTORY "${PROJEC_SOURCE_DIR}"
      OUTPUT_VARIABLE PROJ_VER_SHA1
      RESULT_VARIABLE PROJ_VER_SHA1_ERROR_CODE
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(NOT PROJ_VER_SHA1_ERROR_CODE)
      set(PROJ_VER_SHA1
          ${PROJ_VER_SHA1}
          PARENT_SCOPE)
      message(STATUS "PROJECT VERSION SHA1 (COMMIT HASH): " ${PROJ_VER_SHA1})
    else()
      set(PROJ_VER_SHA1 "")
      message(
        WARNING
          "Failed to determine project version sha1 from GIT TAGS (annotated). Using default version sha1 ${PROJ_VER_SHA1}."
      )
    endif()
    execute_process(
      COMMAND "${GIT_EXECUTABLE}" log -1 --format=%ad --date=local
      WORKING_DIRECTORY "${PROJEC_SOURCE_DIR}"
      OUTPUT_VARIABLE PROJ_VER_DATE
      RESULT_VARIABLE PROJ_VER_DATE_ERROR_CODE
      ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(NOT PROJ_VER_DATE_ERROR_CODE)
      set(PROJ_VER_DATE
          ${PROJ_VER_DATE}
          PARENT_SCOPE)
      message(STATUS "PROJECT VERSION DATE: " ${PROJ_VER_DATE})
    else()
      set(PROJ_VER_SHA1 "")
      message(
        WARNING
          "Failed to determine project version date from GIT TAGS (annotated). Using default version date ${PROJ_VER_DATE}."
      )
    endif()
  else()
    message(
      WARNING
        "Failed to determine project version from GIT TAGS (annotated). Using default version ${PROJ_VER}."
    )
  endif()

endfunction(get_latest_annotated_tag)

# ----------------------------------------------------------------------------
#   Set project version using latest git annotated tag
# ----------------------------------------------------------------------------

# these values are default and will be changed in the get_latest_annotated_tag function
set(PROJ_VER "0.1.0")
set(PROJ_VER_SHA1 "")
set(PROJ_VER_DATE "")

if(ENABLE_AUTOMATIC_VERSIONING)
  get_latest_annotated_tag()
  string(
    REGEX
    REPLACE "^v([0-9a-zA-Z-]+)\\..*"
            "\\1"
            PROJ_VER_MAJOR
            "${PROJ_VER}")
  string(
    REGEX
    REPLACE "^v[0-9a-zA-Z-]+\\.([0-9a-zA-Z-]+).*"
            "\\1"
            PROJ_VER_MINOR
            "${PROJ_VER}")
  string(
    REGEX
    REPLACE "^v[0-9a-zA-Z-]+\\.[0-9a-zA-Z-]+\\.([0-9a-zA-Z-]+).*"
            "\\1"
            PROJ_VER_PATCH
            "${PROJ_VER}")
else()
  set(PROJ_VER_MAJOR 0)
  set(PROJ_VER_MINOR 1)
  set(PROJ_VER_PATCH 0)
endif()

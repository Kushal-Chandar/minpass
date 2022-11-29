include_guard()

include(FetchContent)

# ----------------------------------------------------------------------------
#   If not specified, use the top readme file as the first page
# ----------------------------------------------------------------------------

find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)

if("${PROJECT_SOURCE_DIR}/README.md")
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${PROJECT_SOURCE_DIR}/README.md")
endif()

set(DOXYGEN_QUIET YES)
set(DOXYGEN_CALLER_GRAPH YES)
set(DOXYGEN_CALL_GRAPH YES)
set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_GENERATE_TREEVIEW YES)

set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN NO)

set(DOXYGEN_DOT_IMAGE_FORMAT svg)
set(DOXYGEN_DOT_TRANSPARENT YES)

file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/docs")
set(DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/docs")

# ----------------------------------------------------------------------------
#   https://github.com/jothepro/doxygen-awesome-css v2.1.0
# ----------------------------------------------------------------------------
FetchContent_Declare(
  _doxygen_theme
  GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
  GIT_TAG v2.1.0)
FetchContent_MakeAvailable(_doxygen_theme)

set(DOXYGEN_HTML_EXTRA_STYLESHEET
    "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome.css"
    "${_doxygen_theme_SOURCE_DIR}/doxygen-awesome-sidebar-only.css")

if(Doxygen_FOUND)
  doxygen_add_docs(
    doxygen ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include
    COMMENT
      "Generating documentation - entry file: ${PROJECT_SOURCE_DIR}/docs/html/index.html"
  )
endif()

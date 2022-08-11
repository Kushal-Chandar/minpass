include_guard()

# ----------------------------------------------------------------------------
#   Get processor count to set number of instances
# ----------------------------------------------------------------------------
if(NOT NPROC)
  include(ProcessorCount)
  ProcessorCount(NPROC)
  if(NPROC EQUAL 0)
    message(FATAL_ERROR "could not get processor count")
  endif()
endif()

find_package(PythonInterp)
if(PYTHON_EXECUTABLE)
  find_program(RUN-CLANG-TIDY NAMES run-clang-tidy)
  if(RUN-CLANG-TIDY)
    add_custom_target(
      clang-tidy
      COMMAND ${PYTHON_EXECUTABLE} ${RUN-CLANG-TIDY}
              -p=${CMAKE_CURRENT_BINARY_DIR} -j ${NPROC} -quiet
      COMMENT "Running clang tidy"
      VERBATIM)
  else()
    message(STATUS "clang-tidy was not found.")
  endif()

  find_program(CPPCHECK NAMES cppcheck)
  find_program(CPPCHECK_HTMLREPORT NAMES cppcheck-htmlreport)
  if(CPPCHECK)
    set(CPPCHECK_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/cppcheck)
    file(MAKE_DIRECTORY ${CPPCHECK_BUILD_DIR})
    add_custom_target(
      cpp-check
      COMMAND
        ${CPPCHECK} --enable=all --inline-suppr --language=c++
        --std=c++${CMAKE_CXX_STANDARD} -j ${NPROC}
        --project=${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
        --report-progress --inconclusive --verbose
        --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/cppcheck_suppressions.txt
        --cppcheck-build-dir=${CPPCHECK_BUILD_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include --xml 2>
        ${CPPCHECK_BUILD_DIR}/cpp-check-report.xml
      COMMAND
        ${PYTHON_EXECUTABLE} ${CPPCHECK_HTMLREPORT}
        --file=${CPPCHECK_BUILD_DIR}/cpp-check-report.xml
        --report-dir=${CPPCHECK_BUILD_DIR}/html
        --source-dir=${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Running cpp-check"
      VERBATIM)
  else()
    message(STATUS "cppcheck was not found.")
  endif()

  find_program(IWYU_TOOL NAMES iwyu_tool.py)
  if(IWYU_TOOL)
    add_custom_target(
      iwyu
      COMMAND ${PYTHON_EXECUTABLE} ${IWYU_TOOL} -p ${CMAKE_CURRENT_BINARY_DIR}
              -j ${NPROC}
      COMMENT "Running include-what-you-use"
      VERBATIM)
  else()
    message(STATUS "include-what-you-use was not found.")
  endif()
else()
  message(STATUS "python was not found cannot run static analyzers.")
endif()

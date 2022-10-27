include_guard()

add_library(coverage_options INTERFACE)

# todo: integrate in github workflow
if(CODE_COVERAGE)
  target_compile_options(
    coverage_options
    INTERFACE -O0
              -g
              -fprofile-instr-generate
              -fcoverage-mapping)
  target_link_options(
    coverage_options
    INTERFACE
    -fprofile-instr-generate
    -fcoverage-mapping)
endif()

enable_testing()
add_subdirectory(tests)

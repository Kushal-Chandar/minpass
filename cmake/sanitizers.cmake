include_guard()

if(SANITIZE_ADDRESS)
  target_compile_options(project_compile_options INTERFACE -fsanitize=address)
  target_link_options(project_compile_options INTERFACE -fsanitize=address)
endif()

if(SANITIZE_UNDEFINED)
  target_compile_options(project_compile_options
                         INTERFACE -fsanitize=undefined,nullability)
  target_link_options(project_compile_options INTERFACE
                      -fsanitize=undefined,nullability)
endif()

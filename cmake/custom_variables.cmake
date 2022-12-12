include_guard()

# -----------------------------------------------------------------------------------
#   Setting custom variables
# if your project name is cmake-init
# CMAKE_INIT_PUBLIC_HEADER_DIR variable -> public headers (include/${PROJECT_NAME})
# CMAKE_INIT_PRIVATE_HEADER_DIR variable -> private headers (src/inc)
# CMAKE_INIT_SOURCE_DIR variable -> source files (src)
# CMAKE_INIT_IMPL_DIR variable -> implementation (src/impl)
# CMAKE_INIT_TEST_DIR variable -> implementation (test)
# -----------------------------------------------------------------------------------
set(${PROJECT_NAME_UPPER}_PUBLIC_HEADER_DIR
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(${PROJECT_NAME_UPPER}_PRIVATE_HEADER_DIR ${PROJECT_SOURCE_DIR}/src/inc)
set(${PROJECT_NAME_UPPER}_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(${PROJECT_NAME_UPPER}_TEST_DIR ${PROJECT_SOURCE_DIR}/tests)
set(${PROJECT_NAME_UPPER}_IMPL_DIR ${PROJECT_SOURCE_DIR}/src/impl)

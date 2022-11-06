# ----------------------------------------------------------------------------
#   Dependency graph visualization
# ----------------------------------------------------------------------------
set(GRAPHVIZ_CUSTOM_TARGETS TRUE)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/graphviz)
find_program(DOT NAMES "dot")
if(DOT)
  message(STATUS "graphviz and dot were found.")
  add_custom_target(
    graphviz
    COMMAND ${CMAKE_COMMAND} "--graphviz=graphviz/dependency.dot" .
    COMMAND ${DOT} -Tsvg graphviz/dependency.dot -o graphviz/dependency.svg
    COMMAND ${DOT} -Tpng graphviz/dependency.dot -o graphviz/dependency.png
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
else()
  message(STATUS "graphviz and dot were not found.")
endif()

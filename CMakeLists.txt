cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "pessum")
set(PROJECT_TYPE "lib")
set(PROJECT_LIB "pessum")
set(PROJECT_EXE "pessum_exe")

project(${PROJECT_NAME})

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/.cmake)

set(CMAKE_CXX_FLAGS "-g -Wall")
set(LIBS)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})
file(GLOB_RECURSE INCLUDE_FILES ${PROJECT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE TEST_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/source/main.cpp)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_LIB} ${SRC_FILES})
add_executable(${PROJECT_EXE} ${PROJECT_SOURCE_DIR}/source/main.cpp)

target_link_libraries(${PROJECT_EXE} ${PROJECT_LIB})

target_link_libraries(${PROJECT_EXE} ${LIBS})

if (${PROJECT_TYPE} STREQUAL "lib")
  install(TARGETS ${PROJECT_LIB} DESTINATION lib)
  install(FILES ${INCLUDE_FILES} DESTINATION include/${PROJECT_NAME})
elseif (${PROJECT_TYPE} STREQUAL "exe")
  install(TARGETS ${PROJECT_EXE} DESTINATION bin)
endif()

option(BUILD_TESTS "Build all test." OFF)

# unit-test
if (BUILD_TESTS)
  add_subdirectory(external/googletest)

  enable_testing()

  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  add_executable(unit-test ${TEST_FILES})

  target_link_libraries(unit-test gtest gtest_main)
  target_link_libraries(unit-test ${PROJECT_LIB})
  target_link_libraries(unit-test ${LIBS})

  add_test(unittest unit-test)

  # Coverage
  if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    setup_target_for_coverage(coverage unit-test coverage)

    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
  endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"

endif()

# Uninstall
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/.cmake/cmake_uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# Link_Commands
add_custom_target(link_commands ALL
  COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json")

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json" "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")

#Sphinx
option(DOCS "Create documentation target." ON)
if (DOCS)
  find_package(Sphinx REQUIRED)

  if(NOT DEFINED SPHINX_THEME)
    set(SPHINX_THEME default)
  endif()

  if(NOT DEFINED SPHINX_THEME_DIR)
    set(SPHINX_THEME_DIR)
  endif()

  set(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/_build")
  set(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_doctrees")
  set(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/html")
  set(SPHINX_LATEX_DIR "${CMAKE_CURRENT_BINARY_DIR}/latex")

  add_custom_target(docs
    COMMAND ${SPHINX_EXECUTABLE} -q -b html -c "${CMAKE_CURRENT_SOURCE_DIR}/docs/" -d "${SPHINX_CACHE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/docs/" "${SPHINX_HTML_DIR}"
    COMMAND ${SPHINX_EXECUTABLE} -q -b latex -c "${CMAKE_CURRENT_SOURCE_DIR}/docs/" -d "${SPHINX_CACHE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/docs/" "${SPHINX_LATEX_DIR}")

  set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${BINARY_BUILD_DIR}" "${SPHINX_CACHE_DIR}" "${SPHINX_HTML_DIR}" "${SPHINX_LATEX_DIR}")
endif()

cmake_minimum_required(VERSION 3.1)

project(pessum)

enable_language(C)
enable_language(CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

set(CMAKE_CXX_STANDARD 11)

file(GLOB SRC
  "${PROJECT_SOURCE_DIR}/source/*.cpp"
  "${PROJECT_SOURCE_DIR}/source/*.hpp"
  )
LIST(REMOVE_ITEM SRC "${PROJECT_SOURCE_DIR}/source/main.cpp")

add_library(pessum_lib ${SRC})
add_executable(pessum "${PROJECT_SOURCE_DIR}/source/main.cpp")

target_link_libraries(pessum pessum_lib)

set(GTEST_DIR external/googletest/googletest)

include_directories(
  ${PROJECT_SOURCE_DIR}/${GTEST_DIR}
  ${PROJECT_SOURCE_DIR}/${GTEST_DIR}/include
  )

set(GTEST_SRC
  ${PROJECT_SOURCE_DIR}/${GTEST_DIR}/src/gtest-all.cc
  ${PROJECT_SOURCE_DIR}/${GTEST_DIR}/src/gtest_main.cc
  )

foreach(_src ${GTEST_SRC})
  set_source_files_properties(${_src} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GTEST_SRC})

file(GLOB HEADER
  "${PROJECT_SOURCE_DIR}/source/*.hpp"
  )

file(GLOB TEST
  "${PROJECT_SOURCE_DIR}/test/*.hpp"
  "${PROJECT_SOURCE_DIR}/test/*.cpp"
  )

add_executable(unit-test ${TEST} ${HEADER})

include_directories(${PROJECT_SOURCE_DIR}/source/)

add_dependencies(unit-test googletest)

target_link_libraries(
  unit-test
  googletest
  pessum_lib
  pthread
  gcov
  )

include(CTest)
enable_testing()
add_test(unit ${PROJE}/unit-tests)

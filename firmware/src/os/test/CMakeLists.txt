cmake_minimum_required(VERSION 3.16)

set(SOURCES
  src/timer_test.cpp
  src/list_test.cpp
)

add_library(${CMAKE_PROJECT_NAME}-os-tests ${SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME}-os-tests PRIVATE ../include)
target_include_directories(${CMAKE_PROJECT_NAME}-os-tests PRIVATE ${GTEST_INCLUDE})
target_include_directories(${CMAKE_PROJECT_NAME}-os-tests PRIVATE ${GMOCK_INCLUDE})

target_link_libraries(${CMAKE_PROJECT_NAME}-os-tests ${OS_BIN})
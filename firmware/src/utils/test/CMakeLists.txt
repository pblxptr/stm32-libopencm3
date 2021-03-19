cmake_minimum_required(VERSION 3.16)

set(SOURCES
  src/list_test.cpp
  src/ring_buffer_test.cpp
)

add_library(${CMAKE_PROJECT_NAME}-utils-tests ${SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME}-utils-tests PRIVATE ../include)
target_include_directories(${CMAKE_PROJECT_NAME}-utils-tests PRIVATE ${GTEST_INCLUDE})
target_include_directories(${CMAKE_PROJECT_NAME}-utils-tests PRIVATE ${GMOCK_INCLUDE})

target_link_libraries(${CMAKE_PROJECT_NAME}-utils-tests ${HAL_BIN})
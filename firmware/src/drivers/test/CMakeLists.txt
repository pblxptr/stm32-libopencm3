cmake_minimum_required(VERSION 3.16)

set(SOURCES
  src/dummy.cpp
)

include_directories(${GTEST_INCLUDE})
include_directories(${GMOCK_INCLUDE})

add_library(${CMAKE_PROJECT_NAME}-drivers-tests ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}-drivers-tests ${GTEST_BIN} pthread)
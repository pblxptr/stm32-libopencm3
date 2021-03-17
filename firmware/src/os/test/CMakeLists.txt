cmake_minimum_required(VERSION 3.16)

set(SOURCES
  src/timer_tests.cpp
)

include_directories(${GTEST_INCLUDE})
include_directories(${GMOCK_INCLUDE})

add_executable(Os_tests ${SOURCES})

# # target_link_libraries(${CMAKE_PROJECT_NAME} gtest_main)
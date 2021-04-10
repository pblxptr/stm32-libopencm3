cmake_minimum_required(VERSION 3.16)

set(SOURCES
  src/list_test.cpp
  src/ring_buffer_test.cpp
)

SET(PROJECT_NAME ${CMAKE_PROJECT_NAME}-utils-tests)

add_library(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} googletest)

target_include_directories(${PROJECT_NAME} PRIVATE ../include)
target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE})
target_include_directories(${PROJECT_NAME} PRIVATE ${GMOCK_INCLUDE})

target_link_libraries(${CMAKE_PROJECT_NAME}-utils-tests ${HAL_BIN})
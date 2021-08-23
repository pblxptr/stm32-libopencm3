cmake_minimum_required(VERSION 3.16)

set(SOURCES
  src/timer_test.cpp
)

SET(PROJECT_NAME ${CMAKE_PROJECT_NAME}-os-tests)

add_library(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} googletest)

target_include_directories(${CMAKE_PROJECT_NAME}-os-tests PRIVATE ../include)
target_include_directories(${CMAKE_PROJECT_NAME}-os-tests PRIVATE ${GTEST_INCLUDE})
target_include_directories(${CMAKE_PROJECT_NAME}-os-tests PRIVATE ${GMOCK_INCLUDE})

target_link_libraries(${CMAKE_PROJECT_NAME}-os-tests 
  ${OS_BIN}
)
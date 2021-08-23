cmake_minimum_required(VERSION 3.16)

set(SOURCES
  src/dummy.cpp
)

SET(PROJECT_NAME ${CMAKE_PROJECT_NAME}-drivers-tests)

add_library(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} googletest)
add_dependencies(${PROJECT_NAME} gsl)

target_include_directories(${CMAKE_PROJECT_NAME}-drivers-tests PUBLIC mocks)

target_link_libraries(${CMAKE_PROJECT_NAME}-drivers-tests 
  pthread
  ${DRIVERS_BIN}
)
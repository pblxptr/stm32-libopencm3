cmake_minimum_required(VERSION 3.16)
project(Henhouse-UnitTests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unittests_bin)

set(CMAKE_CXX_FLAGS "-g -std=c++17")

set(COMPILER_CXX_FLAGS "-fno-use-cxa-atexit -O3 -fno-exceptions -g -std=c++17")
set(COMPILER_FLAGS "-fdata-sections -ffunction-sections -Wall -Wextra -save-temps -pedantic-errors")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "${COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMPILER_CXX_FLAGS} ${COMPILER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS}")

include($ENV{CMAKE_ADDONS}/common.cmake)

### EXTERNAL LIBRARIES ###
include($ENV{CMAKE_ADDONS}/unittests_external_libraries.cmake)

### SOURCES ###
add_subdirectory($ENV{SOURCE_DIR}/os os)
add_subdirectory($ENV{SOURCE_DIR}/os/test os-tests)

add_subdirectory($ENV{SOURCE_DIR}/drivers drivers)
add_subdirectory($ENV{SOURCE_DIR}/drivers/test drivers-tests)

add_subdirectory($ENV{SOURCE_DIR}/devices devices)
add_subdirectory($ENV{SOURCE_DIR}/devices/test devices-tests)

add_subdirectory($ENV{SOURCE_DIR}/utils utils)
add_subdirectory($ENV{SOURCE_DIR}/utils/test utils-tests)

add_subdirectory($ENV{SOURCE_DIR}/hal hal)
add_subdirectory($ENV{SOURCE_DIR}/platform/${PLATFORM} platform)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
add_dependencies(${CMAKE_PROJECT_NAME} googletest)

target_link_libraries(${CMAKE_PROJECT_NAME}
  ${GTEST_BIN} 
  pthread
  ${OS_BIN}
  -Wl,--whole-archive ${CMAKE_PROJECT_NAME}-os-tests
  -Wl,--whole-archive ${CMAKE_PROJECT_NAME}-drivers-tests
  -Wl,--whole-archive ${CMAKE_PROJECT_NAME}-devices-tests
  -Wl,--whole-archive ${CMAKE_PROJECT_NAME}-utils-tests
  -Wl,--no-whole-archive
)




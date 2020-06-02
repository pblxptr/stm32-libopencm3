cmake_minimum_required(VERSION 3.16)
project(Os_tests)

set(UTILS_PATH /home/pp/STM32/STM32_Template/src/utils)
set(OS_PATH /home/pp/STM32/STM32_Template/src/os)

set(SOURCES
  src/TimerTests.cpp
  ${OS_PATH}/src/Timer.cpp
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



set(COMPILER_CXX_FLAGS "-fno-use-cxa-atexit -O0 -fno-exceptions -g")

set(GTEST_PATH /home/pp/STM32/STM32_Template/lib/googletest)
set(GTEST_OUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/googletest)

include_directories(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${CMAKE_PROJECT_NAME} ${UTILS_PATH}/include)

add_subdirectory(${GTEST_PATH} ${GTEST_OUT_PATH})
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

link_directories(${CMAKE_PROJECT_NAME} ${CMAKE_CURRENT_BINARY_DIR}/lib)

message(INFO ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${CMAKE_PROJECT_NAME} gtest_main)
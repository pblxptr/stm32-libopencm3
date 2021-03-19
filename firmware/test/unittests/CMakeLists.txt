cmake_minimum_required(VERSION 3.16)
project(Henhouse-UnitTests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unittests_bin)

set(CMAKE_CXX_FLAGS "-g -std=c++17")

include($ENV{REPO_ROOT}/common.cmake)

### SOURCES ###
add_subdirectory($ENV{SOURCE_DIR}/os xd)
add_subdirectory($ENV{SOURCE_DIR}/os/test dd)



cmake_minimum_required(VERSION 3.0.0)
project(cpptest)

SET(sources
  main.cpp
  devices_ln/src/esp8266wlan.cpp
  utils_ln/src/ring_buffer.cpp
  utils_ln/src/console_print.cpp
)

add_executable(cpptest ${sources})

set_property(TARGET cpptest PROPERTY CXX_STANDARD 17)

set(COMPILER_CXX_FLAGS "-g")
set(CMAKE_BUILD_TYPE Debug)

include_directories(utils_ln/include)
include_directories(devices_ln/include)
include_directories(drivers_ln/include)
include_directories(hal_ln/include)
include_directories(hal_platform_linux)

target_link_libraries(${CMAKE_PROJECT_NAME} -pthread)

find_package(fmt REQUIRED)
include_directories(${fmt_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} fmt::fmt)


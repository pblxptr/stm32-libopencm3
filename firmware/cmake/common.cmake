cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_CPPCHECK "cppcheck")

### CMAKE MODULES ###
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

### PORT CONFIGURATIOM ### 
include($ENV{SOURCE_DIR}/board/${BOARD}/board.cmake)

### TOOLCHAIN ###
include($ENV{TOOLS_DIR}/toolchains/${TOOLCHAIN}_toolchain.cmake)

### COMPILE DEFINITIONS ###
add_compile_definitions(TRACE_LEVEL=${TRACE_LEVEL})

### PROJECT PACKAGES ###
set(APP_BIN       ${CMAKE_PROJECT_NAME})
set(UTILS_BIN     ${CMAKE_PROJECT_NAME}_utils)
set(DRIVERS_BIN   ${CMAKE_PROJECT_NAME}_drivers)
set(OS_BIN        ${CMAKE_PROJECT_NAME}_os)
set(BOARD_BIN      ${CMAKE_PROJECT_NAME}_board)
set(PLATFORM_BIN  ${CMAKE_PROJECT_NAME}_${PLATFORM})
set(HAL_BIN       ${CMAKE_PROJECT_NAME}_hal)
set(DEVICES_BIN  ${CMAKE_PROJECT_NAME}_devices)
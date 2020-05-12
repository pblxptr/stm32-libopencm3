cmake_minimum_required(VERSION 3.16)
project(stm32-template)

set(CMAKE_ASM_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_C_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/arm-none-eabi-g++")

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# GENERAL PATHS 
set(PORT_DIR ${PROJECT_SOURCE_DIR}/src/port/${PORT})

# LIBRARIES 
set(LIBOPENCM3_PATH ${PROJECT_SOURCE_DIR}/lib/libopencm3)
set(LIBOPENCM3_INCLUDE ${LIBOPENCM3_PATH}/include)
ExternalProject_Add(libopencm3
    SOURCE_DIR "${LIBOPENCM3_PATH}"
    BUILD_IN_SOURCE true
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_COMMAND make
)

# ADD LIBRARY INCLUDES 
include_directories(${LIBOPENCM3_INCLUDE})

# PORT CONFIGURATIOM 
include(${PORT_DIR}/port.cmake)

add_subdirectory(src)
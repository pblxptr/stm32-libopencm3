cmake_minimum_required(VERSION 3.16)
project(stm32-template)

# COMPILER JUST TEMPORARY TODO: REMOVE!!!
set(CMAKE_ASM_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_C_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/arm-none-eabi-g++")

# CMAKE MODULES
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# GENERAL PATHS 
set(PORT_DIR ${PROJECT_SOURCE_DIR}/src/port/${PORT})
set(TOOLS_PATH ${PROJECT_SOURCE_DIR}/tools)

# PORT CONFIGURATIOM 
include(${PORT_DIR}/port.cmake)

# COMPILER CONFIGURATION
set(COMPILER_CXX_FLAGS "-fno-use-cxa-atexit -Og -fno-exceptions -g")
set(COMPILER_FLAGS "-fdata-sections -ffunction-sections -DNDEBUG -Wall -Werror -save-temps")
set(LINKER_FLAGS "-nostartfiles -specs=nano.specs -u ISR_TAG_WORKAROUND -specs=nosys.specs --static -ggdb3 -Wl,--gc-sections -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group -Wl,-Map=output.map -T ${LD_SCRIPT}")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "${COMPILER_FLAGS} ${ARCH_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMPILER_CXX_FLAGS} ${COMPILER_FLAGS} ${ARCH_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS} ${ARCH_FLAGS}")

# LIBRARIES 
set(LIBOPENCM3_PATH ${PROJECT_SOURCE_DIR}/lib/libopencm3)
set(LIBOPENCM3_INCLUDE ${LIBOPENCM3_PATH}/include)
set(LIBOPENCM3_BIN ${LIBOPENCM3_PATH}/lib/libopencm3_${MCU_FAMILY}.a)
ExternalProject_Add(libopencm3
    SOURCE_DIR "${LIBOPENCM3_PATH}"
    BUILD_IN_SOURCE true
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_COMMAND make
)

set(GTEST_PATH ${PROJECT_SOURCE_DIR}/lib/googletest)
set(GTEST_BIN ${GTEST_PATH}/lib/libgtest.a)
set(GTEST_MAIN_BIN ${GTEST_PATH}/lib/libgtest_main.a)
set(GMOCK_BIN ${GTEST_PATH}/lib/libgmock.a)
set(GTEST_INCLUDE ${GTEST_PATH}/googletest/include)
set(GMOCK_INLCUDE ${GTEST_PATH}/googlemock/include)
ExternalProject_Add(gtest
    SOURCE_DIR "${GTEST_PATH}"
    BUILD_IN_SOURCE true
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_COMMAND ""
)


# ADD LIBRARY INCLUDES 
include_directories(${LIBOPENCM3_INCLUDE})
include_directories(${GTEST_INCLUDE})
include_directories(${GMOCK_INLCUDE})

# SUBDIRECTORIS 
add_subdirectory(src)

# CUSTOM COMMANDS 
add_custom_target(flash
  COMMAND python ${TOOLS_PATH}/flash.py ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_PROJECT_NAME}.hex STM32F103C8
  COMMENT "CMake flashing target."

  #DEPENDS {EXE_NAME}
)
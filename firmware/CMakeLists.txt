cmake_minimum_required(VERSION 3.16)
project(Hh-firmware)

include(common.cmake)

set(COMPILER_CXX_FLAGS "-fno-use-cxa-atexit -O3 -fno-exceptions -g -std=c++17")
set(COMPILER_FLAGS "-fdata-sections -ffunction-sections -Wall -Wextra -save-temps -pedantic-errors -fdump-tree-all")
set(LINKER_FLAGS "-nostartfiles -specs=nano.specs -u ISR_TAG_WORKAROUND -specs=nosys.specs --static -ggdb3 -Wl,--gc-sections -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group -Wl,-Map=output.map -T ${LD_SCRIPT}")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "${COMPILER_FLAGS} ${ARCH_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMPILER_CXX_FLAGS} ${COMPILER_FLAGS} ${ARCH_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS} ${ARCH_FLAGS}")

add_subdirectory(src)

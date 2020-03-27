cmake_minimum_required(VERSION 3.12)
project(stm32-template)

enable_language(ASM)

set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")

set(LIBOPENCM3 ${PROJECT_SOURCE_DIR}/lib/libopencm3)
set(LIBOPENCM3_SRC ${LIBOPENCM3}/lib/stm32)
set(PORT_DIR ${PROJECT_SOURCE_DIR}/src/port/${PORT})

include(${PORT_DIR}/port.cmake)

set(COMPILER_CXX_FLAGS "-fno-use-cxa-atexit")
set(COMPILER_FLAGS "-fdata-sections -ffunction-sections -O0 -DNDEBUG -Werror")
set(LINKER_FLAGS "-nostartfiles -specs=nano.specs -specs=nosys.specs --static -ggdb3 -Wl,--gc-sections -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group -Wl,-Map=output.map -T ${LD_SCRIPT}")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "${COMPILER_FLAGS} ${ARCH_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMPILER_CXX_FLAGS} ${COMPILER_FLAGS} ${ARCH_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS} ${ARCH_FLAGS}")

include_directories(${LIBOPENCM3}/include)
include_directories(${PORT_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src/drivers/include)
include_directories(${PROJECT_SOURCE_DIR}/src/types/include)
include_directories(${PROJECT_SOURCE_DIR}/src/sys/include)
include_directories(${PROJECT_SOURCE_DIR}/src/utils/include)
include_directories(${PROJECT_SOURCE_DIR}/src/app/include)

add_custom_target(libopencm3 COMMAND make run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/libopencm3
    #DEPENDS {EXE_NAME}
)

set(COMMON_SRC 
  ${LIBOPENCM3}/lib/cm3/nvic.c
  ${LIBOPENCM3}/lib/cm3/vector.c
  ${LIBOPENCM3}/lib/cm3/systick.c
  ${PROJECT_SOURCE_DIR}/src/sys/src/sys_timer.c
  ${PROJECT_SOURCE_DIR}/src/utils/src/delay.c
  ${PROJECT_SOURCE_DIR}/src/types/src/ring_buffer.c
  ${PROJECT_SOURCE_DIR}/src/drivers/src/led.c
  ${PROJECT_SOURCE_DIR}/src/drivers/src/hd44780.c
  ${PROJECT_SOURCE_DIR}/src/drivers/src/rotary_encoder.c
  ${PROJECT_SOURCE_DIR}/src/drivers/src/gps.c
  ${PROJECT_SOURCE_DIR}/src/drivers/src/hal/exti.c
)

set(PORT_SRC 
    ${RCC_SRC}
    ${GPIO_SRC}
    ${ISR_SRC}
    ${I2C_SRC}
    ${EXTI_SRC}
    ${USART_SRC}
    ${USB_SRC}
)

set(EXE_NAME STM32Run)

add_executable(${EXE_NAME} 
  ${PROJECT_SOURCE_DIR}/src/app/src/main.c 
  ${PROJECT_SOURCE_DIR}/src/app/src/exti_hal_adapter.c 
  ${PROJECT_SOURCE_DIR}/src/app/src/usart_hal_adapter.c 
  ${PROJECT_SOURCE_DIR}/src/app/src/ec_bus.c 
  ${PROJECT_SOURCE_DIR}/src/app/src/ec_bus_transport.c 
  ${PORT_SRC} 
  ${COMMON_SRC})

target_link_libraries(${EXE_NAME} m)

add_custom_command(TARGET ${EXE_NAME} POST_BUILD
  COMMAND arm-none-eabi-objcopy -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}.hex
  COMMAND arm-none-eabi-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME}
  COMMAND cp ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE_NAME} debug.elf
)

add_custom_target(flash
  COMMAND JLinkExe -device STM32F103C8 -If SWD -Speed 1000 -CommandFile tools/jlink/FlashCommand.jlink
  COMMENT "asd"

  #DEPENDS {EXE_NAME}
)

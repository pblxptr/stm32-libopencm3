
set(SOURCES
  hal/plt_hal_gpio.cpp
  hal/plt_hal_uart.cpp
  uart/ll_uart.cpp
  dma/ll_dma.cpp
  gpio/ll_gpio.cpp
)

add_library(${PLATFORM_BIN} STATIC ${SOURCES})

target_link_libraries(${PLATFORM_BIN}
  ${DRIVERS_BIN}
  ${LIBOPENCM3_BIN}
)

target_include_directories(${PLATFORM_BIN} PUBLIC ../include)
target_include_directories(${PLATFORM_BIN} PUBLIC config)
target_include_directories(${PLATFORM_BIN} PUBLIC platform)
target_include_directories(${PLATFORM_BIN} PUBLIC hal)

target_include_directories(${PLATFORM_BIN} PUBLIC uart)
target_include_directories(${PLATFORM_BIN} PUBLIC dma)
target_include_directories(${PLATFORM_BIN} PUBLIC gpio)

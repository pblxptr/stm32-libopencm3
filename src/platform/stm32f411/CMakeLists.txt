
set(SOURCES
  hal/plt_hal_gpio.cpp
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
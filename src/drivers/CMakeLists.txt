set(SOURCES
  src/gps.c
  src/hd44780.c
  src/led.c
  src/rotary_encoder.c
  src/hal/exti.c 
)

add_library(${DRIVERS_BIN} STATIC ${SOURCES})

target_include_directories(${DRIVERS_BIN} PUBLIC include)

target_link_libraries(${DRIVERS_BIN}  ${LIBOPENCM3_PATH})
target_link_libraries(${DRIVERS_BIN}  ${UTILS_BIN})
target_link_libraries(${DRIVERS_BIN}  ${SYS_BIN})
target_link_libraries(${DRIVERS_BIN}  ${PORT_BIN})
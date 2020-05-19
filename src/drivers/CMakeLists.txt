set(SOURCES
  src/gps.c
  src/hd44780.c
  src/led.c
  src/rotary_encoder.c
  src/hal/exti.c 
  src/Led.cpp
)

add_library(${DRIVERS_BIN} STATIC ${SOURCES})

target_include_directories(${DRIVERS_BIN} PUBLIC include)

target_link_libraries(${DRIVERS_BIN}  
  ${LIBOPENCM3_BIN}
  ${UTILS_BIN}
  ${SYS_BIN}
  ${PORT_BIN}
)
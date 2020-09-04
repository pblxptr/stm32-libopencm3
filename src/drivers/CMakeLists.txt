set(SOURCES
  src/Led.cpp
  src/Gpio.cpp
  src/Esp8266Wlan.cpp
)

add_library(${DRIVERS_BIN} STATIC ${SOURCES})

target_include_directories(${DRIVERS_BIN} PUBLIC include)

target_link_libraries(${DRIVERS_BIN}  
  ${LIBOPENCM3_BIN}
  ${UTILS_BIN}
  ${OS_BIN}
  ${PORT_BIN}
)
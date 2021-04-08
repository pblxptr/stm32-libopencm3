set(SOURCES
  src/esp8266wlan.cpp
)

add_library(${DEVICES_BIN} STATIC ${SOURCES})

target_include_directories(${DEVICES_BIN} PUBLIC include)

target_link_libraries(${DEVICES_BIN}
  ${HAL_BIN}
  ${OS_BIN}
  ${UTILS_BIN}
)
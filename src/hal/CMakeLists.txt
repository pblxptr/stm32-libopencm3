set(SOURCES
  src/dummy.cpp
  src/uart.cpp
)

add_library(${HAL_BIN} STATIC ${SOURCES})

target_include_directories(${HAL_BIN} PUBLIC include)

target_link_libraries(${HAL_BIN}
  ${DRIVERS_BIN}
  ${PLATFORM_BIN}
)
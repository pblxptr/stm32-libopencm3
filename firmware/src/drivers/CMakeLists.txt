set(SOURCES
  src/uart.cpp
)

add_library(${DRIVERS_BIN} STATIC ${SOURCES})
add_dependencies(${DRIVERS_BIN} gsl)

target_include_directories(${DRIVERS_BIN} PUBLIC include)

target_link_libraries(${DRIVERS_BIN}
  ${PLATFORM_BIN}
  ${OS_BIN}
  ${HAL_BIN}
)
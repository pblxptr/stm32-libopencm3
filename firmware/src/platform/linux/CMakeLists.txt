set(SOURCES
  hal/plt_hal_uart.cpp
)

add_library(${PLATFORM_BIN} STATIC ${SOURCES})

target_link_libraries(${PLATFORM_BIN}
  ${DRIVERS_BIN}
)


# add_library(${PLATFORM_BIN} INTERFACE ${SOURCES})

# target_link_libraries(${PLATFORM_BIN}
#   ${DRIVERS_BIN}
# )
target_include_directories(${PLATFORM_BIN} PUBLIC ../include)

target_include_directories(${PLATFORM_BIN} PUBLIC hal)

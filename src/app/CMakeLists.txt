set(SOURCES
 src/main.cpp
)

add_executable(${APP_BIN} ${SOURCES})

target_include_directories(${APP_BIN} PRIVATE include)

target_link_libraries(${APP_BIN}
  ${LIBOPENCM3_BIN}
  ${DRIVERS_BIN}
  ${SYS_BIN}  
  ${UTILS_BIN}
)

add_custom_command(TARGET ${APP_BIN} POST_BUILD
  COMMAND arm-none-eabi-objcopy -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP_BIN} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP_BIN}.hex
  COMMAND arm-none-eabi-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP_BIN}
  COMMAND cp ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP_BIN} debug.elf
)

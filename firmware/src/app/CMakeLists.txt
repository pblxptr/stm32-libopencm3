set(SOURCES
  src/main.cpp
  # src/main_test.cpp
  # src/main_test_master.cpp
  # src/server.cpp
)

add_executable(${APP_BIN} ${SOURCES})

target_include_directories(${APP_BIN} PRIVATE include)

target_link_libraries(${APP_BIN}
  # ${BOARD_BIN}
  # ${LIBOPENCM3_BIN}
  ${DRIVERS_BIN}
  # ${OS_BIN}  
  ${UTILS_BIN}
  ${PLATFORM_BIN}
  ${HAL_BIN}
  ${DEVICES_BIN}
)

add_custom_command(TARGET ${APP_BIN} POST_BUILD
  COMMAND arm-none-eabi-objcopy -O ihex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP_BIN} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP_BIN}.hex
  COMMAND arm-none-eabi-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP_BIN}
  COMMAND cp ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP_BIN} debug.elf
)

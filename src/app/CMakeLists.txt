set(SOURCES
  src/main.c
)

add_executable(${APP_BIN} ${SOURCES})

target_include_directories(${APP_BIN} PRIVATE include)

target_link_libraries(${APP_BIN}
  ${LIBOPENCM3_PATH}
  ${DRIVERS_BIN}
  ${SYS_BIN}  
  ${UTILS_BIN}
)
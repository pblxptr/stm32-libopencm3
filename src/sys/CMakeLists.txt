set(SOURCES
  src/sys_timer.c
)

add_library(${SYS_BIN} STATIC ${SOURCES})

target_include_directories(${SYS_BIN} PUBLIC include)

target_link_libraries(${SYS_BIN}  ${UTILS_BIN})
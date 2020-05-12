
set(SOURCES
  src/isr.c
)

add_library(${PORT_BIN} STATIC ${SOURCES})

target_include_directories(${PORT_BIN} PUBLIC include)
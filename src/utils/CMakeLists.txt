
set(SOURCES
  include/delay.h
  include/list.h
  include/ring_buffer.h
)

add_library(${UTILS_BIN} INTERFACE)

target_include_directories(${UTILS_BIN} INTERFACE include)
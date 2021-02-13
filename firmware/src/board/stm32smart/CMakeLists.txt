
set(SOURCES
  src/isr.cpp
)

add_library(${BOARD_BIN} STATIC ${SOURCES})

target_link_libraries(${BOARD_BIN}
  # ${OS_BIN}  
)

target_include_directories(${BOARD_BIN} PUBLIC include)
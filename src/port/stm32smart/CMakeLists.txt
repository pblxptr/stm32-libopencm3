
set(SOURCES
  src/isr.cpp
)

add_library(${PORT_BIN} STATIC ${SOURCES})

target_link_libraries(${PORT_BIN}
  ${OS_BIN}  
)

target_include_directories(${PORT_BIN} PUBLIC include)
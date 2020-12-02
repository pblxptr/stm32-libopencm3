set(SOURCES
  src/dummy.cpp
)

add_library(${DRIVERS_BIN} STATIC ${SOURCES})

target_include_directories(${DRIVERS_BIN} PUBLIC include)

target_link_libraries(${DRIVERS_BIN}
  ${PLATFORM_BIN}
)
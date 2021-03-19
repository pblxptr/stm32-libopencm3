set(SOURCES
  src/timer.cpp
  src/list.cpp
)

add_library(${OS_BIN} STATIC ${SOURCES})

target_include_directories(${OS_BIN} PUBLIC include)

# target_link_libraries(${OS_BIN} ${UTILS_BIN} )
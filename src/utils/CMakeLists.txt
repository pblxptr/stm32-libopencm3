cmake_minimum_required(VERSION 3.16)

set(SOURCES
  include/delay.h
  include/list.h
  include/ring_buffer.h
  src/uprintf.cpp
)

add_library(${UTILS_BIN} STATIC ${SOURCES})

target_include_directories(${UTILS_BIN} INTERFACE include) #TODO: Remove this line because of one below?
target_include_directories(${UTILS_BIN} PUBLIC include)
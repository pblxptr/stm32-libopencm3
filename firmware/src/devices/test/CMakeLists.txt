cmake_minimum_required(VERSION 3.16)

set(SOURCES
  src/esp8266_wlan_test.cpp
  src/template_inst_helper.cpp
)

include_directories(${GTEST_INCLUDE})
include_directories(${GMOCK_INCLUDE})

add_library(${CMAKE_PROJECT_NAME}-devices-tests ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}-devices-tests 
  ${GMOCK_BIN}  
  ${DEVICES_BIN}
  ${CMAKE_PROJECT_NAME}-drivers-tests
)
cmake_minimum_required(VERSION 3.16)

### LIBOPENCM3 ###
set(LIBOPENCM3_PATH $ENV{EXTERNAL_LIB_DIR}/libopencm3)
set(LIBOPENCM3_INCLUDE ${LIBOPENCM3_PATH}/include)
set(LIBOPENCM3_BIN ${LIBOPENCM3_PATH}/lib/libopencm3_${MCU_FAMILY}.a)
ExternalProject_Add(libopencm3
  GIT_REPOSITORY    https://github.com/libopencm3/libopencm3
  GIT_TAG           master
  SOURCE_DIR        $ENV{EXTERNAL_LIB_DIR}/libopencm3
  BUILD_IN_SOURCE   true
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     "make"
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
include_directories(${LIBOPENCM3_INCLUDE})
### LIBOPENCM3 ###
set(LIBOPENCM3_PATH $ENV{EXTERNAL_LIB_DIR}/libopencm3)
set(LIBOPENCM3_INCLUDE ${LIBOPENCM3_PATH}/include)
set(LIBOPENCM3_BIN ${LIBOPENCM3_PATH}/lib/libopencm3_${MCU_FAMILY}.a)
ExternalProject_Add(libopencm3
  GIT_REPOSITORY    https://github.com/libopencm3/libopencm3
  GIT_TAG           master
  SOURCE_DIR        $ENV{EXTERNAL_LIB_DIR}/libopencm3
  BUILD_IN_SOURCE true
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     "make"
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
include_directories(${LIBOPENCM3_INCLUDE})

### GTEST ###
# set(GTEST_PATH $ENV{EXTERNAL_LIB_DIR}/googletest)
# set(GTEST_BIN ${GTEST_PATH}/lib/libgtest.a)
# set(GTEST_MAIN_BIN ${GTEST_PATH}/lib/libgtest_main.a)
# set(GMOCK_BIN ${GTEST_PATH}/lib/libgmock.a)
# set(GTEST_INCLUDE ${GTEST_PATH}/googletest/include)
# set(GMOCK_INLCUDE ${GTEST_PATH}/googlemock/include)

ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        $ENV{EXTERNAL_LIB_DIR}/googletest
  BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
include_directories(${GTEST_INCLUDE})
include_directories(${GMOCK_INLCUDE})


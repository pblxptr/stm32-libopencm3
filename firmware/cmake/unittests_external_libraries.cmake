cmake_minimum_required(VERSION 3.16)

### GTEST ###
set(GTEST_PATH $ENV{EXTERNAL_LIB_DIR}/googletest)
set(GTEST_BIN ${GTEST_PATH}/lib/libgtest.a)
set(GTEST_MAIN_BIN ${GTEST_PATH}/lib/libgtest_main.a)
set(GMOCK_BIN ${GTEST_PATH}/lib/libgmock.a)
set(GTEST_INCLUDE ${GTEST_PATH}/googletest/include)
set(GMOCK_INLCUDE ${GTEST_PATH}/googlemock/include)

ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        $ENV{EXTERNAL_LIB_DIR}/googletest
  BUILD_IN_SOURCE   true
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ${CMAKE_COMMAND} -E echo "Starting $<CONFIG> build"
  COMMAND           ${CMAKE_COMMAND} $ENV{EXTERNAL_LIB_DIR}/googletest && make
  COMMAND           ${CMAKE_COMMAND} -E echo "$<CONFIG> build complete"
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
include_directories(${GTEST_INCLUDE})
include_directories(${GMOCK_INLCUDE})

### GSL ###
set(GSL_PATH $ENV{EXTERNAL_LIB_DIR}/gsl)
set(GSL_INCLUDE ${GSL_PATH}/include)

ExternalProject_Add(gsl
  GIT_REPOSITORY    https://github.com/microsoft/GSL
  GIT_TAG           main
  SOURCE_DIR        $ENV{EXTERNAL_LIB_DIR}/gsl
  BUILD_IN_SOURCE   true
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ${CMAKE_COMMAND} -E echo "Starting $<CONFIG> build"
  COMMAND           ${CMAKE_COMMAND} $ENV{EXTERNAL_LIB_DIR}/gsl && make
  COMMAND           ${CMAKE_COMMAND} -E echo "$<CONFIG> build complete"
  INSTALL_COMMAND   ""
  TEST_COMMAND      "ctest"
)
include_directories(${GSL_INCLUDE})
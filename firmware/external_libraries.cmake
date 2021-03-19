### LIBOPENCM3 ###
set(LIBOPENCM3_PATH ${PROJECT_SOURCE_DIR}/lib/libopencm3)
set(LIBOPENCM3_INCLUDE ${LIBOPENCM3_PATH}/include)
set(LIBOPENCM3_BIN ${LIBOPENCM3_PATH}/lib/libopencm3_${MCU_FAMILY}.a)
ExternalProject_Add(libopencm3
    SOURCE_DIR "${LIBOPENCM3_PATH}"
    BUILD_IN_SOURCE true
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    INSTALL_COMMAND ""
    BUILD_COMMAND make
)
include_directories(${LIBOPENCM3_INCLUDE})

### GTEST ###
# set(GTEST_PATH ${PROJECT_SOURCE_DIR}/lib/googletest)
# set(GTEST_BIN ${GTEST_PATH}/lib/libgtest.a)
# set(GTEST_MAIN_BIN ${GTEST_PATH}/lib/libgtest_main.a)
# set(GMOCK_BIN ${GTEST_PATH}/lib/libgmock.a)
# set(GTEST_INCLUDE ${GTEST_PATH}/googletest/include)
# set(GMOCK_INLCUDE ${GTEST_PATH}/googlemock/include)
# ExternalProject_Add(gtest
#     SOURCE_DIR "${GTEST_PATH}"
#     BUILD_IN_SOURCE true
#     DOWNLOAD_COMMAND ""
#     CONFIGURE_COMMAND ""
#     INSTALL_COMMAND ""
#     BUILD_COMMAND ""
# )
# include_directories(${GTEST_INCLUDE})
# include_directories(${GMOCK_INLCUDE})


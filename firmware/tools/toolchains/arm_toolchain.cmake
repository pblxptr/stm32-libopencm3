set(CMAKE_ASM_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_C_COMPILER "/usr/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/arm-none-eabi-g++")

add_custom_target(flash
  COMMAND python $ENV{TOOLS_DIR}/flash.py $ENV{BUILD_DIR}/bin/${CMAKE_PROJECT_NAME}.hex ${TARGET_MCU}
  COMMENT "CMake flashing target."
)

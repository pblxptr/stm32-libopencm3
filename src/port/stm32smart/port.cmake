set(LD_SCRIPT /home/pp/STM32/STM32_Template/src/port/stm32smart/ld/STM32F103C8Tx_FLASH.ld)

SET(RCC_SRC 
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/rcc_common_all.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/flash_common_all.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/f1/rcc.c
)

add_compile_definitions(STM32F1)
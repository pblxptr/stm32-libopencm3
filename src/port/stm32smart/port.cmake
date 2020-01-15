set(LD_SCRIPT /home/pp/STM32/STM32_Template/src/port/stm32smart/ld/STM32F103C8Tx_FLASH.ld)

set(RCC_SRC 
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/rcc_common_all.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/flash_common_all.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/f1/rcc.c
)

set(GPIO_SRC
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/f1/gpio.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/gpio_common_all.c
)

add_compile_definitions(STM32F1)
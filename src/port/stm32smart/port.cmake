set(LD_SCRIPT /home/pp/STM32/STM32_Template/src/port/stm32smart/ld/STM32F103C8Tx_FLASH.ld)
set(TARGET_MCU "STM32F103C8T6")

set(RCC_SRC 
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/rcc_common_all.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/flash_common_all.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/f1/rcc.c
)

set(GPIO_SRC
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/f1/gpio.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/gpio_common_all.c
)

set(I2C_SRC
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/f1/i2c.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/i2c_common_v1.c
)

set(ISR_SRC
  ${PORT_DIR}/src/isr.c
)

set(EXTI_SRC
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/exti_common_all.c
)

set(USART_SRC
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/usart_common_all.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/usart_common_f124.c
)

set(USB_SRC
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/st_usbfs_v1.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/stm32/common/st_usbfs_core.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/usb/usb.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/usb/usb_control.c
  /home/pp/STM32/STM32_Template/lib/libopencm3/lib/usb/usb_standard.c
)


set(ARCH_FLAGS "-mcpu=cortex-m3 -mthumb -mfpu=vfp")

add_compile_definitions(STM32F1)
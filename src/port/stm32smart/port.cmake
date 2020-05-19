set(LD_SCRIPT /home/pp/STM32/STM32_Template/src/port/stm32smart/ld/STM32F103C8Tx_FLASH.ld)
set(TARGET_MCU "STM32F103C8T6")
set(MCU_FAMILY "stm32f1") #TODO: Remove, the information of mcu family shoud be obtained from TARGET_MCU.

set(ARCH_FLAGS "-mcpu=cortex-m3 -mthumb -mfpu=vfp")

add_compile_definitions(STM32F1)
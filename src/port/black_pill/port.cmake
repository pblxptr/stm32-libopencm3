set(LD_SCRIPT /home/pp/STM32/HenhouseCtrl/firmware/src/port/black_pill/ld/stm32f405x6.ld)
set(TARGET_MCU "STM32F411CE")
set(MCU_FAMILY "stm32f4") #TODO: Remove, the information of mcu family shoud be obtained from TARGET_MCU.
set(ARCH_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")

add_compile_definitions(STM32F4)
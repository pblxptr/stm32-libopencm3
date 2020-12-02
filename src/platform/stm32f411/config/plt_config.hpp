#pragma once

#include <stdint.h>

namespace platform::config
{
  //Gpio
  constexpr uint32_t BLUE_LED_GPIO = 0; 
  constexpr uint32_t RED_LED1_GPIO = 1;
  constexpr uint32_t RED_LED2_GPIO = 2;
  constexpr uint32_t RED_LED3_GPIO = 3;
  
  //Uart
  constexpr uint32_t SERIAL1 = USART1;
  constexpr uint32_t CONSOLE = USART2;
}
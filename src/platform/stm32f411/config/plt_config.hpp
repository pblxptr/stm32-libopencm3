#pragma once

#include <stdint.h>

namespace platform::config
{
  //Gpio
  constexpr uint32_t BLUE_LED_GPIO = 45; 
  constexpr uint32_t RED_LED1_GPIO = 5;
  constexpr uint32_t RED_LED2_GPIO = 6;
  constexpr uint32_t RED_LED3_GPIO = 7;

  //Uart
  constexpr uint32_t SERIAL1 = USART1;
  constexpr uint32_t SERIAL1_GPIO_RX = 9;
  constexpr uint32_t SERIAL1_GPIO_TX = 10;

  constexpr uint32_t CONSOLE = USART2;
  constexpr uint32_t CONSOLE_GPIO_RX = 2;
  constexpr uint32_t CONSOLE_GPIO_TX = 3;
}
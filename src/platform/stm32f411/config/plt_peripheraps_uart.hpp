#pragma once

extern "C" {
  #include <libopencm3/stm32/usart.h>
}

#include <drivers/gpio.hpp>

namespace platform::peripherals::uart
{
  constexpr uint32_t usarts[] = {
    USART1,
    USART2,
    USART3,
    UART4
  };
}